#include "phone.h"
#include <sstream>
#include <iostream>

Module::Module(double weight) : weight_(weight) {}
double Module::getWeight() const { return weight_; }

Battery::Battery(int mAh, double weight) : Module(weight), mAh_(mAh) {}
int Battery::getCapacity() const { return mAh_; }
std::string Battery::describe() const {
    std::ostringstream oss;
    oss << "Battery(" << mAh_ << " mAh, " << getWeight() << " g)";
    return oss.str();
}

Camera::Camera(double mp, double weight) : Module(weight), mp_(mp) {}
double Camera::getMegapixels() const { return mp_; }
std::string Camera::describe() const {
    std::ostringstream oss;
    oss << "Camera(" << mp_ << " Mp, " << getWeight() << " g)";
    return oss.str();
}

Antenna::Antenna(Signal signal, double weight) : Module(weight), signal_(signal) {}
Antenna::Signal Antenna::getSignal() const { return signal_; }
std::string Antenna::signalName() const {
    switch (signal_) {
    case Signal::G2: return "2G";
    case Signal::G3: return "3G";
    case Signal::G4: return "4G";
    case Signal::G5: return "5G";
    }
    return "?G";
}
std::string Antenna::describe() const {
    std::ostringstream oss;
    oss << "Antenna(" << signalName() << ", " << getWeight() << " g)";
    return oss.str();
}

Phone::Phone(const std::string& name, double baseWeight)
    : name_(name), baseWeight_(baseWeight),
    battery_(nullptr), camera_(nullptr), antenna_(nullptr) {
}

Phone::~Phone() {
    delete battery_;
    delete camera_;
    delete antenna_;
}

bool Phone::hasPower() const { return battery_ != nullptr; }

Battery* Phone::add(Battery* b) { Battery* old = battery_; battery_ = b; return old; }
Camera* Phone::add(Camera* c) { Camera* old = camera_;  camera_ = c; return old; }
Antenna* Phone::add(Antenna* a) { Antenna* old = antenna_; antenna_ = a; return old; }

Battery* Phone::removeBattery() { Battery* b = battery_; battery_ = nullptr; return b; }
Camera* Phone::removeCamera() { Camera* c = camera_;  camera_ = nullptr; return c; }
Antenna* Phone::removeAntenna() { Antenna* a = antenna_; antenna_ = nullptr; return a; }

void Phone::call() const {
    if (!hasPower()) throw std::runtime_error("No battery.");
    if (!antenna_)   throw std::runtime_error("No antenna.");
    std::cout << "*Beep-Beep*\n";
}

void Phone::photo() const {
    if (!hasPower()) throw std::runtime_error("No battery.");
    if (!camera_)    throw std::runtime_error("No camera.");
    std::cout << "*Click*\n";
}

double Phone::totalWeight() const {
    double w = baseWeight_;
    if (battery_) w += battery_->getWeight();
    if (camera_)  w += camera_->getWeight();
    if (antenna_) w += antenna_->getWeight();
    return w;
}

std::string Phone::getName() const { return name_; }

std::ostream& operator<<(std::ostream& os, const Phone& p) {
    os << "Name: " << p.name_ << " | Weight: " << p.totalWeight() << " g | Modules: [";
    bool first = true;
    if (p.battery_) { os << p.battery_->describe(); first = false; }
    if (p.camera_) { if (!first) os << ", "; os << p.camera_->describe();  first = false; }
    if (p.antenna_) { if (!first) os << ", "; os << p.antenna_->describe(); }
    if (!p.battery_ && !p.camera_ && !p.antenna_) os << "none";
    os << "]";
    return os;
}

Phone* PhoneFactory::create(const std::string& modelName) {
    if (modelName == "Pon M10") {
        Phone* p = new Phone("Pon M10");
        p->add(new Battery(4000));
        p->add(new Camera(5));
        p->add(new Antenna(Antenna::Signal::G3));
        return p;
    }
    if (modelName == "Pon M10 Pro") {
        Phone* p = new Phone("Pon M10 Pro");
        p->add(new Battery(3000));
        p->add(new Camera(25));
        p->add(new Antenna(Antenna::Signal::G4));
        return p;
    }
    if (modelName == "Pon M10 Pro Max") {
        Phone* p = new Phone("Pon M10 Pro Max");
        p->add(new Battery(2800));
        p->add(new Camera(40));
        p->add(new Antenna(Antenna::Signal::G5));
        return p;
    }
    throw std::invalid_argument("Unknown model: \"" + modelName + "\"");
}