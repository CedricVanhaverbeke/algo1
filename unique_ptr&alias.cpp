#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Entity;

using EntityPointer = unique_ptr<Entity>;

class Entity {
   public:
    Entity() { cout << "Object gemaakt" << endl; }

    ~Entity() { cout << "Object gedestroyed"; }

    void print() {}
};

int main() {
    {
        EntityPointer entity = make_unique<Entity>();
        entity->print();
    };

    return 0;
}