#include <opencv2/opencv.hpp>
#include <opencv2/stitching.hpp>
#include <filesystem>
#include <iostream>
#include <algorithm>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    // === 1. Preluare parametri din linia de comandă ===
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <folder_path> [output_name] [projection: cylindrical|spherical|plane] [inside]\n";
        return 1;
    }

    std::string folderPath = argv[1];
    std::string outputName = (argc > 2) ? argv[2] : "imagine_finala.jpg";
    std::string projection = (argc > 3) ? argv[3] : "cylindrical";
    bool inside = (argc > 4 && std::string(argv[4]) == "inside");

    // === 2. Încarcă imaginile din folder și sortează ===
    std::vector<std::pair<std::string, cv::Mat>> imageList;
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().filename().string();
            std::string ext = entry.path().extension().string();
            std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
            if ((ext == ".jpg" || ext == ".jpeg" || ext == ".png" || ext == ".bmp" || ext == ".tif" || ext == ".tiff") && filename != outputName) {
                cv::Mat img = cv::imread(entry.path().string());
                if (!img.empty()) {
                    imageList.emplace_back(filename, img);
                    std::cout << "✅ Încărcat: " << filename << "\n";
                }
            }
        }
    }

    if (imageList.size() < 2) {
        std::cerr << "❌ Sunt necesare cel puțin 2 imagini valide în folderul: " << folderPath << "\n";
        return 1;
    }

    // Sortează alfabetic după nume
    std::sort(imageList.begin(), imageList.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;
    });

    // Extrage doar imaginile
    std::vector<cv::Mat> images;
    for (const auto& p : imageList)
        images.push_back(p.second);

    std::cout << "\n➡️  " << images.size() << " imagini vor fi lipite într-o panoramă...\n";

    // === 3. Configurare Stitcher ===
    cv::Ptr<cv::Stitcher> stitcher = cv::Stitcher::create(cv::Stitcher::PANORAMA);
    stitcher->setPanoConfidenceThresh(0.65);
    stitcher->setSeamEstimationResol(0.5);
    stitcher->setRegistrationResol(0.6);
    stitcher->setCompositingResol(-1);
    stitcher->setWaveCorrection(true);
    stitcher->setWaveCorrectKind(cv::detail::WAVE_CORRECT_HORIZ);

    // Setare warper în funcție de proiecție
    if (projection == "spherical")
        stitcher->setWarper(cv::makePtr<cv::SphericalWarper>());
    else if (projection == "plane")
        stitcher->setWarper(cv::makePtr<cv::PlaneWarper>());
    else
        stitcher->setWarper(cv::makePtr<cv::CylindricalWarper>()); // default

    // === 4. Aplică Stitching ===
    cv::Mat pano;
    cv::Stitcher::Status status = stitcher->stitch(images, pano);

    if (status != cv::Stitcher::OK) {
        std::cerr << "❌ Stitching eșuat! Cod eroare = " << static_cast<int>(status) << "\n";
        return 1;
    }

    // === 5. Dacă s-a cerut curbura interioară, inversează imaginea ===
    if (inside) {
        std::cout << "🔄 Aplic proiecție inversă (curbură spre interior)...\n";
        if (inside) {
    std::cout << "🔄 Aplic curbura interioară (proiecție inversă)...\n";

    cv::Mat inversePano(pano.size(), pano.type());
    int w = pano.cols;
    int h = pano.rows;
    float f = w / 2.0f;  // distanța focală aproximativă

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            float theta = (x - w / 2.0f) / f;
            float srcX = w / 2.0f - f * std::tan(theta);  // inversăm direcția unghiului
            float srcY = y;
            if (srcX >= 0 && srcX < w)
                inversePano.at<cv::Vec3b>(y, x) = pano.at<cv::Vec3b>(y, (int)srcX);
        }
    }

    pano = inversePano.clone();
}

    }

    // === 6. Decupare automată pentru eliminarea negrului ===
    cv::Mat gray, mask;
    cv::cvtColor(pano, gray, cv::COLOR_BGR2GRAY);
    cv::threshold(gray, mask, 10, 255, cv::THRESH_BINARY);

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    if (!contours.empty()) {
        size_t largestIdx = 0;
        double maxArea = 0;
        for (size_t i = 0; i < contours.size(); ++i) {
            double area = cv::contourArea(contours[i]);
            if (area > maxArea) { maxArea = area; largestIdx = i; }
        }

        cv::Rect cropRect = cv::boundingRect(contours[largestIdx]);
        cv::Mat cropped = pano(cropRect).clone();

        // === 7. Retușare zone negre rămase (inpainting) ===
        cv::Mat maskBlack;
        cv::inRange(cropped, cv::Scalar(0,0,0), cv::Scalar(0,0,0), maskBlack);
        cv::inpaint(cropped, maskBlack, cropped, 3, cv::INPAINT_TELEA);

        // === 8. Salvare rezultat ===
        std::string finalPath = folderPath + "/" + outputName;
        if (cv::imwrite(finalPath, cropped))
            std::cout << "\n✅ Panorama salvată ca: " << finalPath << "\n";
        else
            std::cerr << "❌ Eroare la salvarea imaginii rezultate.\n";
    } else {
        std::cerr << "❌ Nu s-a putut determina zona utilă pentru decupare.\n";
    }

    return 0;
}
