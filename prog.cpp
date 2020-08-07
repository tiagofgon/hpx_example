
#include "heranca.hpp"

#include <hpx/hpx_main.hpp>

typedef int mytype;

REGISTER_C(mytype)

int main(){

    
    // Create C<T> class component and run getIdp action, witch belong to B<T> class component
    hpx::future<hpx::id_type> f = hpx::local_new<C<mytype>>(7);
    typedef typename C<mytype>::getIdp_action action_type;
    auto c = f.get();
	auto value = hpx::async<action_type>(c).get();
    std::cout << "idp value is: " << value << std::endl;


    return 0;
}