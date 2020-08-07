

#include <hpx/include/actions.hpp>
#include <hpx/include/components.hpp>


///////////////////////////////////////////////////////////////////////////////
// Struct A
struct A : hpx::components::component_base<A>
{
    A() = default;
    ~A() = default;

};

// HPX_REGISTER_COMPONENT is on heranca.cpp



///////////////////////////////////////////////////////////////////////////////
// Struct B templated
template <typename T>
struct B : hpx::components::component_base<B<T>>
{
    B() = default;
    ~B() = default;

    B(int idp) :
        _idp{idp}
    {}

    int getIdp() const
    {
        return _idp;
    }

    HPX_DEFINE_COMPONENT_ACTION(B, getIdp);

    private:
        int _idp;
};

#define REGISTER_B_DECLARATION(type)                           \
    HPX_REGISTER_ACTION_DECLARATION(                           \
        B<type>::getIdp_action,                                \
        HPX_PP_CAT(__B_getIdp_action_, type));                 \

/**/

#define REGISTER_B(type)                                       \
    HPX_REGISTER_ACTION(                                       \
        B<type>::getIdp_action,                                \
        HPX_PP_CAT(__B_getIdp_action_, type));                 \
  typedef ::hpx::components::component<                        \
      B<type>>                                                 \
      HPX_PP_CAT(__B_, type);                                  \
  HPX_REGISTER_COMPONENT(HPX_PP_CAT(__B_, type))               \
  /**/



///////////////////////////////////////////////////////////////////////////////
// Struct C templated derived from A and B<T>
template <typename T>
struct C : hpx::components::component_base<C<T>>, public A, public B<T>
{
    typedef typename hpx::components::component_base<C<T>>::wrapping_type wrapping_type;
    typedef typename hpx::components::component_base<C<T>>::wrapped_type wrapped_type;

    using hpx::components::component_base<C<T>>::finalize;
    using hpx::components::component_base<C<T>>::get_base_gid;
    using hpx::components::component_base<C<T>>::get_current_address;

    typedef C type_holder;
    typedef B<T> base_type_holder;


    C() = default;
    ~C() = default;

    C(int idp) :
        B<T>{idp}
    {}

};


#define REGISTER_C(type)                                       \
    REGISTER_B(type);                                          \
    typedef ::hpx::components::component<                      \
        C<type>>                                               \
        HPX_PP_CAT(__C_, type);                                \
    HPX_REGISTER_COMPONENT(HPX_PP_CAT(__C_, type))             \

