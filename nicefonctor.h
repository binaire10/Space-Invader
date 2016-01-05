#ifndef NICEFONCTOR
#define NICEFONCTOR
/**
 * @file nicefonctor.h
 * \brief All basic fonctor are here
 * @author (binaire) Alexandre Wery
 */

/**
 * @struct equalOP
 * \brief The equalOP struct
 * structor to replace operator == for find
 */
struct equalOP
{
    template<typename X, typename Y>
    /**
     * \brief operator ()
     * fonctor of equal operator
     * @param k
     * @param y
     * @return
     */
    bool operator()(const X &k, const Y &y)
    { return k==y;}
};

/**
 * @struct deletePtr
 * \brief The deletePtr struct
 * delete pointer in parameter
 */
struct deletePtr
{
    template<typename X>
    /**
     * \brief operator ()
     * fonctor to delete ptr
     * @param k
     */
    void operator()(X *k)
    { delete k;}
};

#endif // NICEFONCTOR

