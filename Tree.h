//
// Created by Nitzan on 06/05/2018.
//

#ifndef CODE_TREE_H
#define CODE_TREE_H

template <class Data, class Key>
class Tree {
    Key* key; // need to think
    Data* data;
    Tree* lson;
    Tree* rson;
    int h_left;
    int h_right;

public:
    Tree(Key& key, Data& data): data(data), key(key), lson(nullptr), rson(nullptr){
        h_left = 0;
        h_right = 0;
    }

    ~Tree(){
        delete lson;
        delete rson;
    }

    Tree& find(Key& key) {
        if (this == nullptr) {
            return *this; //exception!!!!!!!!!!!
        }
        if (this->key == key) {
            return *this;
        }
        else {
            if (this->key > key) {
                return this->lson->find(key);
            }
            else {
                return this->rson->find(key);
            }
        }
    }

    Tree(const Tree& tree) = delete; //h


};

#endif //CODE_TREE_H
