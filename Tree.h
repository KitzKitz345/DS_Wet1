//
// Created by Nitzan on 06/05/2018.
//

#ifndef CODE_TREE_H
#define CODE_TREE_H

#include <exception>

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

    int max(int a, int b)
    {
        if (a > b){
            return a;
        } else {
            return b;
        }
    }

    void LL_Roll () {
        int size_lson = this->lson->size;
        this->lson->size = this->size;
        this->size = size_lson-1;

        //this->h_left = this->lson->h_right;
        //this->lson->h_right++;

        Tree* ptr_lson = this->lson;
        this->lson = this->lson->rson;
        ptr_lson->rson = this;

        if (this->father->lson == this) {
            this->father->lson = ptr_lson;
        }
        if (this->father->rson == this) {
            this->father->rson = ptr_lson;
        }
        this->father = ptr_lson;

        this->update_heights();
        this->father->update_heights();
    }

    void RR_Roll () {
        int size_rson = this->rson->size;
        this->rson->size = this->size;
        this->size = size_rson-1;

        //this->h_right = this->rson->h_left;
        //this->rson->h_left++;

        Tree* ptr_rson = this->rson;
        this->rson = this->rson->lson;
        ptr_rson->lson = this;

        if (this->father->lson == this) {
            this->father->lson = ptr_rson;
        }
        if (this->father->rson == this) {
            this->father->rson = ptr_rson;
        }
        this->father = ptr_rson;

        this->update_heights();
        this->father->update_heights();
    }

    void LR_Roll () {
        this->lson->RR_Roll();
        this->LL_Roll();
    }

    void RL_Roll () {
        this->rson->LL_Roll();
        this->RR_Roll();
    }

    void find_roll(){
        int BF = this->h_left - this->h_right;
        int lson_BF = this->lson->h_left - this->lson->h_right;
        int rson_BF = this->rson->h_left - this->rson->h_right;
        if (BF == 2){
            if(lson_BF >= 0){
                this->LL_Roll_insert();
            } else if (lson_BF == -1){
                this->LR_Roll_insert();
            }
        } else if (BF == -2){
            if(lson_BF <= 0){
                this->RR_Roll_insert();
            } else if (lson_BF == 1){
                this->RL_Roll_insert();
            }
        }
    }

    void update_heights(){
        Tree* T = this;
        if (T->lson != nullptr){
            T->h_left = 1+ max(T->lson->h_left, T->lson->h_right);
        }
        if (T->rson != nullptr){
            T->h_right = 1 + max(T->rson->h_left, T->rson->h_right);
        }
    }

    void balance() {
        Tree* T = this;
        while(T->father != nullptr){
            Tree* current_father = T->father;
            //calculate heights before insertion
            int father_height = max(current_father->h_right, current_father->h_left) + 1;
            int son_height = max(T->h_right, T->h_left) + 1;
            if (father_height >= son_height+1){
                current_father->update_heights();
                return;
            }
            current_father->update_heights();
            int BF = current_father->h_left - current_father->h_right;
            if(BF >= 2 || BF <= -2){
                current_father->find_roll();
                return;
            } else {
                T = current_father;
            }
        }
    }

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
    class EmptyTree : public std::exception {};

    Tree& find(Key& key) {
        if (this->data == nullptr) {
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
        if (this->data == nullptr) {
            return data; //exception!!!!!!!!!!
        }
        this->lson->inorder(data++);
        data = this->data;
        data++;
        this->rson->inorder(data++);
        return data;
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
        } else {
            T->rson = new Tree(key, data);
            T->rson->father = T;
            T = T->rson;
        }
        T->balance();
        while(T != nullptr){
            T->size++;
            T = T->father;
        }
    }
};

#endif //CODE_TREE_H
