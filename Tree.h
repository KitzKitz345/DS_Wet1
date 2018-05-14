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
        if (BF == 2){
            int lson_BF = this->lson->h_left - this->lson->h_right;
            if(lson_BF >= 0){
                this->LL_Roll();
            } else if (lson_BF == -1){
                this->LR_Roll();
            }
        } else if (BF == -2){
            int rson_BF = this->rson->h_left - this->rson->h_right;
            if(rson_BF <= 0){
                this->RR_Roll();
            } else if (rson_BF == 1){
                this->RL_Roll();
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
            current_father->update_heights();
            int BF = current_father->h_left - current_father->h_right;
            if(BF >= 2 || BF <= -2){
                current_father->find_roll();
            }
            T = current_father;
        }
    }

    void remove_leaf(){
        Tree* parent = this->father;
        bool is_left_son = parent->lson->key == key;
        if (is_left_son){
            //delete parent->lson;
            parent->lson = nullptr;
            parent->h_left  = 0;
        } else {
            //delete parent->rson;
            parent->rson = nullptr;
            parent->h_right = 0;
        }
        while (parent != nullptr){
            parent->size--;
            parent = parent->father;
        }
    }

    void remove_only_one_son(){
        Tree* parent = this->father;
        bool is_left_son = parent->lson->key == key;
        Tree* only_son = nullptr;
        if (this->lson == nullptr){
            only_son = this->rson;
        } else {
            only_son = this->lson;
        }
        if (is_left_son){
            //delete parent->lson;
            parent->lson = only_son;
            parent->h_left--;
        } else {
            //delete parent->rson;
            parent->rson = only_son;
            parent->h_right--;
        }
        while (parent != nullptr){
            parent->size--;
            parent = parent->father;
        }
    }

    void switch_nodes(Tree& to_switch){
        Tree* temp_tree = this->father;
        if (temp_tree->lson->key == this->key) {
            temp_tree->lson = &to_switch;
        }else{
            temp_tree->rson = &to_switch;
        }
        if (to_switch.father->lson->key == to_switch.key){
            to_switch.father->lson = this;
        } else {
            to_switch.father->rson = this;
        }
        this->father = to_switch.father;
        to_switch.father = temp_tree;

        temp_tree = this->lson;
        this->lson = to_switch.lson;
        to_switch.lson = temp_tree;

        temp_tree = this->rson;
        this->rson = to_switch.rson;
        to_switch.rson = temp_tree;

        int temp_int = this->h_left;
        this->h_left = to_switch.h_left;
        to_switch.h_left = temp_int;

        temp_int = this->h_right;
        this->h_right = to_switch.h_right;
        to_switch.h_right = temp_int;

        temp_int = this->size;
        this->size = to_switch.size;
        to_switch.size = temp_int;
    }

    void remove_two_sons(Key& key){
        Tree* next_node = this->rson;
        while (next_node->lson != nullptr) {
            next_node = next_node->lson;
        }
        this->switch_nodes(*next_node);
        remove(*(this->key));
    }

public:
    Tree(): key(nullptr), data(nullptr) , father(nullptr), lson(nullptr), rson(nullptr), h_left(0),
            h_right(0), size(0){}

    Tree(Key& key, Data& data): key(&key), data(&data), father(nullptr), lson(nullptr),
                                rson(nullptr), h_left(0), h_right(0), size(0){}

    ~Tree(){
        delete lson;
        delete rson;
        delete key;
    }

    Tree(const Tree& tree) = delete;

    int getSize(){
        return this->size;
    }

    Data& getData(){
        return *(this->data);
    }

    class AlreadyExist : public std::exception {};
    class DoesNotExist : public std::exception {};
    class EmptyTree : public std::exception {};

    Tree& find(Key& key) {
        if (this->data == nullptr) {
            throw EmptyTree();
        }
        if (*(this->key) == key) {
            return *this;
        }
        else {
            if (*(this->key) > key) {
                if (this->lson == nullptr) {
                    return *this;
                } else {
                    return this->lson->find(key);
                }
            }
            else {
                if (this->rson == nullptr) {
                    return *this;
                } else {
                    return this->rson->find(key);
                }
            }
        }
    }

    Data** inorder (Data** data) {
        if (this->data == nullptr) {
            throw EmptyTree();
        }
        if (this->lson != nullptr) {
            data = this->lson->inorder(data);
        }
        *data = this->data;
        data++;
        if (this->rson != nullptr) {
            data = this->rson->inorder(data);
        }
        return data;
    }

    void insert(Key& key, Data& data) {
        if (this->data == nullptr){
            this->key = &key;
            this->data = &data;
            this->size = 1;
            return;
        }
        Tree* T = &(this->find(key));
        if (*(T->key) == key) {
            throw AlreadyExist();
        }
        if (*(T->key) > key){
            T->lson = new Tree(key, data);
            T->lson->father = T;
            T = T->lson;
        } else {
            T->rson = new Tree(key, data);
            T->rson->father = T;
            T = T->rson;
        }
        Tree* T_copy = T;
        T->size++;
        while (T_copy->father != nullptr){
            T_copy->father->size++;
            T_copy = T_copy->father;
        }
        T->balance();
    }

    void remove(Key& key){
        Tree* T = &this->find(key);
        if (*(T->key) != key){
            throw DoesNotExist();
        }
        Tree* parent = T->father;
        //bool is_left_son = *(parent->lson->key) == key;
        if (T->size == 1) {
            T->remove_leaf();
        } else if (T->lson == nullptr || T->rson == nullptr){ //T has only one son
            T->remove_only_one_son();
        } else {
            T->remove_two_sons(key);
        }
        parent->balance();
        delete T;
    }

    void deleteTree () {
        if (this->data == nullptr) {
            throw EmptyTree(); // need to catch this somewhere
        }
        if (this->lson != nullptr && this->lson->lson != nullptr) {
            this->lson->deleteTree();
        }
        if (this->lson != nullptr && this->lson->rson != nullptr) {
            this->lson->deleteTree();
        }
        if (this->rson != nullptr && this->rson->lson != nullptr) {
            this->rson->deleteTree();
        }
        if (this->rson != nullptr && this->rson->rson != nullptr) {
            this->rson->deleteTree();
        }
        delete this->lson->data;
        delete this->rson->data;
        delete this->lson->key;
        delete this->rson->key;
    }
};

#endif //CODE_TREE_H
