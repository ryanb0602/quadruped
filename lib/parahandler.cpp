#include <paracore.h>

int para_handler::current_time() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void para_handler::add_active(parametric to_add, leg *targ) {

    if (this->length == 0) {
        this->ll = new para_handler_ll;

        this->ll->current = to_add;
        this->ll->targ = targ;

        this->last = ll;
        return;
    }

    this->last->ll = new para_handler_ll;
    para_handler_ll *new_ll = this->last->ll;
    this->length += 1;

    this->last = this->last->ll;

    new_ll->current = to_add;
    new_ll->targ = targ;
}

void para_handler::update_all() {
    para_handler_ll *current_ptr = this->ll;
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
            leg_position update_vals = current_para.get_current_vals(current_time() - current_para.get_starttime());
            
            current_ptr->targ->set_ideal_x_y(update_vals);

            current_para.set_lastupdate(this->current_time());
        }

        current_ptr = current_ptr->ll;

    }
}

void para_handler::delete_para(para_handler_ll *ll) {
    if (this->length == 1) {
        delete this->ll;
        this->length--;
        this->last = nullptr;
        return;
    }

    if (ll == this->last) {
        para_handler_ll *current_ptr;
        for (int i = 0; i < this->length - 2; i++) {
            current_ptr = current_ptr->ll;
        }
        this->last = current_ptr;
        delete ll;
        this->length--;
        return;
    }

    para_handler_ll *current_ptr = this->ll;
    para_handler_ll *before_ptr = nullptr;
    while (true) {
        if (current_ptr == ll) {
            break;
        }
        before_ptr = current_ptr;
        current_ptr = current_ptr->ll;
    }

    before_ptr->ll = ll->ll;
    delete ll;
    this->length--;

}