#include "queue.hh"
#include <iostream>
// Implement the member functions of Queue here

Queue::Queue(unsigned int cycle): cycle_(cycle)
{
    
}

Queue::~Queue()
{    
    Vehicle* current = first_;
    while(current != nullptr){
        Vehicle* tmp = current-> prev;
        delete current;
        current = tmp;
    }
}

void Queue::enqueue(string reg)
{
    if(is_green_ and n_ == 0){
        cout<<"GREEN: The vehicle "<<reg<<" need not stop to wait"<<endl;
    }else{
        Vehicle* new_veh = new Vehicle;

        new_veh->next = last_;
        new_veh->prev = nullptr;
        new_veh->reg_num = reg;

        if(last_!= nullptr){
            last_->prev = new_veh;
        }

        last_ = new_veh;

        n_++;

        if(n_==1){
            first_ = last_;
        }
    }
}

void Queue::switch_light()
{
    if(is_green_ == true){
        is_green_ = false;
        Queue::print();
    }else if(is_green_ == false){
        is_green_ = true;
        Queue::print();
        if(n_!=0){
            Vehicle* current = first_;
            unsigned int i=0;
            while(current != nullptr and i<cycle_){
                dequeue();
                current = current->prev;
                i++;
            }
            is_green_ = false;
        }

    }


}

void Queue::reset_cycle(unsigned int cycle)
{
    cycle_ = cycle;
}

void Queue::print()
{
    string color;
    if(is_green_){
        color = "GREEN";
    }else{
        color = "RED";
    }

    cout<<color<<": ";
    if(n_==0){
        std::cout<<"No vehicles waiting in traffic lights"<<endl;;
    }else{
        cout<<"Vehicle(s) ";

        Vehicle* current = first_;
        unsigned int i=0;
        while(current != nullptr and i<cycle_){
            cout<<current->reg_num<<" ";
            current = current->prev;
            if(is_green_){
                i++;
            }
        }

        if(is_green_){
            cout<<"can go on"<<endl;;
        }else{
            cout<<"waiting in traffic lights"<<endl;;
        }
    }


}

void Queue::dequeue()
{
    if(n_!=0){
        Vehicle* second = first_->prev;
        delete first_;
        first_ = second;

        if(first_!= nullptr){
            first_ -> next = nullptr;
        }

        n_--;
        if(n_==0){
            last_ = nullptr;
        }

    }
}
