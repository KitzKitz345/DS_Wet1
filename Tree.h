//
// Created by Nitzan on 06/05/2018.
//

#ifndef CODE_TREE_H
#define CODE_TREE_H

#include <exception>
#include <algorithm>

template <class Data, class Key>
class Tree {
    Key* key; // need to think
    Data* data;
    Tree* father;
    Tree* lson;
    Tree* rson;
    int h_left;
    int h_right;
    int size; // size includes left tree, right tree and current node. needs to add to system description.

public:
    Tree(): data(nullptr), key(nullptr), father(nullptr), lson(nullptr), rson(nullptr){}

    Tree(Key& key, Data& data): data(data), key(key), father(nullptr), lson(nullptr), rson(nullptr){
        h_left = 0;
        h_right = 0;
        size = 0;
    }

    ~Tree(){
        delete lson;
        delete rson;
    }

    Tree(const Tree& tree) = delete;

    class AlreadyExist : public std::exception {};
    //class EmptyTree : public std::exception {};

    Tree& find(Key& key) {
        if (this == nullptr) {
            return *this; //exception!!!!!!!!!!
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

    Data** inorder (Data** data) {
        if (this == nullptr) {
            return data; //exception!!!!!!!!!!
        }
        this->lson->inorder(data++);
        data = this->data;
        data++;
        this->rson->inorder(data++);
        return data;
    }

    void LL_Roll () {
        Tree* temp = this->lson;
        this->lson = this->lson->rson;
        temp->rson = this;
        this->father = temp;
    }

    void LR_Roll () {

    }

    int max(int a, int b)
    {
        if (a > b){
            return a;
        } else {
            return b;
        }
    }

    void update_after_insert(){
        Tree* T = this->father;
        while (T != nullptr){
            int size = 1;
            if (T->lson != nullptr){
                T->h_left = 1+ max(T->lson->h_left, T->lson->h_right);
            }
            if (T->rson != nullptr){
                T->h_right = 1 + max(T->rson->h_left, T->rson->h_right);
            }
            T = T->father;
        }
    }

    void insert(Key& key, Data& data) {
        Tree* T = &this->find(key);
        if (T->data == nullptr){
            T->key = key;
            T->data = data;
            T->size = 1;
            return;
        }
        if (T->key == key) {
            throw AlreadyExist();
        }
        if (T->key > key){
            T->lson = new Tree(key, data);
            T->lson->father = T;
            T = T->lson;
            T->size++;
        } else {
            T->rson = new Tree(key, data);
            T->rson->father = T;
            T = T->rson;
            T->size++;
        }
        T->update_after_insert();
        void balance();
    }
};

#endif //CODE_TREE_H
