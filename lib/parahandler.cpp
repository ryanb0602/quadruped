#include <paracore.h>

int para_handler::current_time() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void para_handler::add_active(parametric to_add, float* a, float* b) {

    if (this->length == 0) {
        this->ll.current = to_add;
        this->ll.a = a;
        this->ll.b = b;

        this->last = &ll;
        return;
    }

    this->last->ll = new para_handler_ll;
    para_handler_ll *new_ll = this->last->ll;
    this->length += 1;

    new_ll->current = to_add;
    new_ll->a = a;
    new_ll->b = b;
}

void para_handler::update_all() {
    para_handler_ll *current_ptr = &this->ll;
    while(true) {

        if (current_ptr == nullptr) {break;}

        parametric current_para = current_ptr->current;
        if (this->current_time() - current_para.get_starttime() >= current_para.get_runtime()) {
            para_handler_ll *to_delete = current_ptr;
            current_ptr = to_delete->ll;
            this->delete_para(current_ptr);
            continue;
        }

        if (this->current_time() - current_para.get_lastupdate() >= (1000 / current_para.get_update_rate())) {
            //update theta vals
        }

        //set nxt ptr

    }
}