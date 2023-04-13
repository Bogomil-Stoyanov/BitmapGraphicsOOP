

#include "Session.h"
#include "iostream"
#include "fstream"

int Session::countOfSessions = 0;

Session::Session() : sessionId(++countOfSessions) {
}

int Session::getId() const {
    return sessionId;
}

void Session::grayscale() {
    unsavedChanges.emplace_back("grayscale");
    for (auto &image: images) {
        if (!image->isGrayscale() && !image->isMonochrome()) {
            image->toGrayscale();
        }
    }

}

void Session::addImage(Image *image) {
    images.push_back(image);
}

void Session::rotate(const std::string &direction) {
    unsavedChanges.emplace_back("rotate " + direction);
    for (auto &image: images) {
        image->rotate(direction);
    }
}

void Session::monochrome() {
    unsavedChanges.emplace_back("monochrome");
    for (auto &image: images) {
        if (!image->isMonochrome()) {
            image->toMonochrome();
        }
    }
}

void Session::save() {
    for (auto &image: images) {
        saveImage(image, image->getFileName());
    }
    unsavedChanges.clear();
}

void Session::negative() {
    unsavedChanges.emplace_back("negative");
    for (auto &image: images) {
        image->toNegative();
    }
}

void Session::saveAs(const std::string &filePath) {
    if (images.empty()) {
        std::cout << "No session" << std::endl;
        return;
    }

    saveImage(images[0], filePath);

    if (images.size() == 1) {
        unsavedChanges.clear();
    }
}

void Session::close() {
    for (auto &image: images) {
        image->removeUnsavedChanges();
    }
}

void Session::undo() {
    if (unsavedChanges.empty()) {
        std::cout << "No changes" << std::endl;
        return;
    }

    for (auto &image: images) {
        image->undo();
    }

    unsavedChanges.pop_back();
}

void Session::saveImage(Image *image, const std::string &filePath) {
    std::ofstream file(filePath);
    image->writeToFile(file);
}

void Session::info() const {

    std::cout << "Session ID: " << sessionId << std::endl;

    std::cout << "Names of images in the session: ";
    for (auto &image: images) {
        std::cout << image->getFileName() << " ";
    }
    std::cout << std::endl;

    if(!unsavedChanges.empty()) {
        std::cout << "Pending transformations: ";
        for (const auto &change: unsavedChanges) {
            std::cout << change << " ";
        }
        std::cout << std::endl;
    }
}

bool Session::hasFile(const std::string &filepath) const {
    for (auto &image: images) {
        if (image->getFileName() == filepath)
            return true;
    }

    return false;
}

bool Session::checkUnsavedChanges() const {
    return unsavedChanges.empty();
}