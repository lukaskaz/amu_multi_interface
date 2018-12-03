#ifndef __CONVERSIONS_H__
#define __CONVERSIONS_H__

#include <sstream>


template <typename T>
class convertNumber {
public:
    convertNumber() = delete;
    convertNumber(const T input, std::ios_base &(*base_ref)(std::ios_base &)):
        base(base_ref), str(""), num(input) {}
    convertNumber(const std::string& input, std::ios_base &(*base_ref)(std::ios_base &)):
        base(base_ref), str(input), num(0)  {}

    const T fromString(void);
    const std::string toString(void);

private:
    std::stringstream stream;

    std::ios_base &(*base)(std::ios_base&);
    const std::string str;
    const T num;
};

template <typename T>
const T convertNumber<T>::fromString(void)
{
    T ret = (-1);

    if(str.size() > 0) {
        for(uint32_t i = 0; i < str.size(); i++) {
            if(isxdigit(str[i]) == 0) {
                return ret;
            }
        }

        stream<<base<<str;
        stream>>ret;
    }

    return ret;
}

template <typename T>
const std::string convertNumber<T>::toString(void)
{
    stream<<std::showbase<<base<<+num<<std::dec;
    return stream.str() + " ";
}


#define CONV_NUM_GET_STR(num_typedef, num_base, num)    \
    convertNumber<num_typedef>((num_typedef)num, std::num_base).toString()

#define CONV_STR_GET_NUM(num_typedef, num_base, string) \
    convertNumber<num_typedef>(string, std::num_base).fromString()

#define PREP_CLASS_NAME (std::string(__func__) + std::string(":"))


#endif
