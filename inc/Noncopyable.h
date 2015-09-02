#ifndef _NONCOPYABLE_H
#define _NONCOPYABLE_H

class Noncopyable
{
protected:
    Noncopyable(){}
    ~Noncopyable(){}

private:
    Noncopyable(const Noncopyable &);
    Noncopyable &operator=(const Noncopyable &);
};

#endif// end _NONCOPYABLE_H
