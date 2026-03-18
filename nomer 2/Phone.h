#pragma once
#include <string>
#include <stdexcept>
#include <ostream>

class Module {
public:
    explicit Module(double weight);
    virtual ~Module() = default;
    double getWeight() const;
    virtual std::string describe() const = 0;
private:
    double weight_;
};

class Battery : public Module {
public:
    Battery(int mAh, double weight = 50.0);
    int getCapacity() const;
    std::string describe() const override;
private:
    int mAh_;
};

class Camera : public Module {
public:
    Camera(double mp, double weight = 20.0);
    double getMegapixels() const;
    std::string describe() const override;
private:
    double mp_;
};

class Antenna : public Module {
public:
    enum class Signal { G2, G3, G4, G5 };
    Antenna(Signal signal, double weight = 15.0);
    Signal getSignal() const;
    std::string signalName() const;
    std::string describe() const override;
private:
    Signal signal_;
};

class Phone {
public:
    Phone(const std::string& name = "Unknown", double baseWeight = 150.0);
    Phone(const Phone&) = delete;
    Phone& operator=(const Phone&) = delete;
    ~Phone();

    Battery* add(Battery* b);
    Camera* add(Camera* c);
    Antenna* add(Antenna* a);

    Battery* removeBattery();
    Camera* removeCamera();
    Antenna* removeAntenna();

    void call()  const;
    void photo() const;

    double      totalWeight() const;
    std::string getName()     const;

    friend std::ostream& operator<<(std::ostream& os, const Phone& p);

private:
    std::string name_;
    double      baseWeight_;
    Battery* battery_;
    Camera* camera_;
    Antenna* antenna_;

    bool hasPower() const;
};

class PhoneFactory {
public:
    static Phone* create(const std::string& modelName);
};
