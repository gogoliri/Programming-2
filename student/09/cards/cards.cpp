#include "cards.hh"

// TODO: Implement the methods here

Cards::Cards():top_(nullptr), bottom_(nullptr), n_(0)
{
    
}

void Cards::add(int id)
{
    Card_data* new_card = new Card_data;

    new_card ->next = top_;
    new_card ->data = id;
    new_card->before = nullptr;

    if(top_ != nullptr){
        top_->before = new_card;
    }

    top_ = new_card;

    n_++;

    if(n_ == 1){
        bottom_ = top_;
    }

}

void Cards::print_from_top_to_bottom(std::ostream &s)
{
    int i = 1;
    Card_data* current = top_;
    while(current != nullptr){
        s<< i <<": "<< current->data<<std::endl;
        i++;
        current = current-> next;
    }
}

bool Cards::remove(int &id)
{
    if(n_ == 0){
        return false;
    }

    id = top_->data;

    Card_data* second = top_->next;

    delete top_;
    top_ = second;

    if(top_!= nullptr){
        top_->before = nullptr;
    }

    n_--;

    if(n_==0){
        bottom_ = nullptr;
    }
    return true;
}

bool Cards::bottom_to_top()
{
    if(n_==0){
        return false;
    }else if(n_ == 1){
        return true;
    }

    Card_data* old_top = top_;
    Card_data* old_bottom = bottom_;
    Card_data* new_bottom = bottom_->before;

    new_bottom->next = nullptr;

    old_bottom->next = old_top;
    old_bottom->before = nullptr;

    old_top->before = old_bottom;

    top_ = old_bottom;
    bottom_ = new_bottom;
    return true;
}

bool Cards::top_to_bottom()
{
    if(n_==0){
        return false;
    }else if(n_ == 1){
        return true;
    }

    Card_data* old_top = top_;
    Card_data* old_bottom = bottom_;
    Card_data* new_top = top_->next;

    new_top->before = nullptr;

    old_top->next = nullptr;
    old_top->before = old_bottom;

    old_bottom->next = old_top;


    top_ = new_top;
    bottom_ = old_top;
    return true;
}

void Cards::print_from_bottom_to_top(std::ostream &s)
{
    int i = 1;
    Card_data* current = bottom_;
    while(current != nullptr){
        s<< i <<": "<< current->data<<std::endl;
        i++;
        current = current-> before;
    }
}

Cards::~Cards()
{
    Card_data* current = top_;
    while(current != nullptr){
        Card_data* tmp = current-> next;
        delete current;
        current = tmp;
    }
}

//int Cards::recursive_print(Cards::Card_data *top, std::ostream &s)
//{

//}
