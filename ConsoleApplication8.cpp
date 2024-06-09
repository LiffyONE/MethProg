#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>

// Абстрактный класс компонента
class BurgerComponent {
public:
    virtual std::string getDescription() const = 0;
    virtual double cost() const = 0;
    virtual ~BurgerComponent() = default;
};

// Конкретный компонент - основа бургера
class BurgerBase : public BurgerComponent {
public:
    std::string getDescription() const override {
        return "Бургер";
    }

    double cost() const override {
        return 100.0; // Базовая цена бургера
    }
};

// Декоратор - добавляет новый ингредиент
class BurgerDecorator : public BurgerComponent {
protected:
    std::shared_ptr<BurgerComponent> burger;
public:
    BurgerDecorator(std::shared_ptr<BurgerComponent> burger) : burger(burger) {}

    std::string getDescription() const override {
        return burger->getDescription();
    }

    double cost() const override {
        return burger->cost();
    }
};

// Конкретные декораторы - различные ингредиенты
class CheeseDecorator : public BurgerDecorator {
public:
    CheeseDecorator(std::shared_ptr<BurgerComponent> burger) : BurgerDecorator(burger) {}

    std::string getDescription() const override {
        return burger->getDescription() + ", сыр";
    }

    double cost() const override {
        return burger->cost() + 20.0; // Цена сыра
    }
};

class BaconDecorator : public BurgerDecorator {
public:
    BaconDecorator(std::shared_ptr<BurgerComponent> burger) : BurgerDecorator(burger) {}

    std::string getDescription() const override {
        return burger->getDescription() + ", бекон";
    }

    double cost() const override {
        return burger->cost() + 30.0; // Цена бекона
    }
};

class PickleDecorator : public BurgerDecorator {
public:
    PickleDecorator(std::shared_ptr<BurgerComponent> burger) : BurgerDecorator(burger) {}

    std::string getDescription() const override {
        return burger->getDescription() + ", маринованные огурцы";
    }

    double cost() const override {
        return burger->cost() + 15.0; // Цена маринованных огурцов
    }
};


class OnionDecorator : public BurgerDecorator {
public:
    OnionDecorator(std::shared_ptr<BurgerComponent> burger) : BurgerDecorator(burger) {}

    std::string getDescription() const override {
        return burger->getDescription() + ", лук";
    }

    double cost() const override {
        return burger->cost() + 10.0; // Цена лука
    }
};

class TomatoDecorator : public BurgerDecorator {
public:
    TomatoDecorator(std::shared_ptr<BurgerComponent> burger) : BurgerDecorator(burger) {}

    std::string getDescription() const override {
        return burger->getDescription() + ", помидор";
    }

    double cost() const override {
        return burger->cost() + 15.0; // Цена помидора
    }
};

class JalapenoDecorator : public BurgerDecorator {
public:
    JalapenoDecorator(std::shared_ptr<BurgerComponent> burger) : BurgerDecorator(burger) {}

    std::string getDescription() const override {
        return burger->getDescription() + ", халапеньо";
    }

    double cost() const override {
        return burger->cost() + 20.0; // Цена халапеньо
    }
};

class KetchupDecorator : public BurgerDecorator {
public:
    KetchupDecorator(std::shared_ptr<BurgerComponent> burger) : BurgerDecorator(burger) {}

    std::string getDescription() const override {
        return burger->getDescription() + ", кетчуп";
    }

    double cost() const override {
        return burger->cost() + 5.0; // Цена кетчупа
    }
};

// Класс-обертка для управления декорированием
class BurgerBuilder {
private:
    std::shared_ptr<BurgerComponent> burger;
    int ingredientCount;

public:
    BurgerBuilder() : burger(std::make_shared<BurgerBase>()), ingredientCount(0) {}

    void addCheese() {
        burger = std::make_shared<CheeseDecorator>(burger);
        ingredientCount++;
    }

    void addBacon() {
        burger = std::make_shared<BaconDecorator>(burger);
        ingredientCount++;
    }

    void addPickle() {
        burger = std::make_shared<PickleDecorator>(burger);
        ingredientCount++;
    }

    void addOnion() {
        burger = std::make_shared<OnionDecorator>(burger);
        ingredientCount++;
    }
    
    void addTomato() {
        burger = std::make_shared<TomatoDecorator>(burger);
        ingredientCount++;
    }

    void addJalapeno() {
        burger = std::make_shared<JalapenoDecorator>(burger);
        ingredientCount++;
    }

    void addKetchup() {
        burger = std::make_shared<KetchupDecorator>(burger);
        ingredientCount++;
    }
    
    std::shared_ptr<BurgerComponent> getBurger() {
        if (ingredientCount < 3) {
            throw std::runtime_error("Необходимо добавить как минимум 3 ингредиента!");
        }
        return burger;
    }
};

// Пример использования
int main() {
    setlocale(LC_ALL, "RUS");
    try {
        BurgerBuilder builder;

        // Добавляем ингредиенты
        builder.addCheese();
        builder.addBacon();
        builder.addPickle();
        //builder.addOnion();
        //.addTomato();
        builder.addJalapeno();
        builder.addKetchup();

        std::shared_ptr<BurgerComponent> burger = builder.getBurger();

        std::cout << "Описание: " << burger->getDescription() << std::endl;
        std::cout << "Цена: " << burger->cost() << " рублей" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
