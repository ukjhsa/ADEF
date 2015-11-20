#ifndef ANY_H
#define ANY_H

#include <memory>
#include <typeindex>
#include <utility>

namespace adef {

/**
@brief Any can store any type.

Any is the simple version to boost::any.
*/
class Any
{
public:

    Any() : content_(nullptr)
    {
    }

    template<typename T>
    Any(const T& value) : content_(std::make_shared<holder<T>>(value))
    {
    }

    Any(const Any& rhs)
    {
        if (rhs.content_) { content_ = rhs.content_->clone(); }
    }

    Any& swap(Any& rhs)
    {
        std::swap(content_, rhs.content_);
        return *this;
    }

    Any& operator=(const Any& rhs)
    {
        Any(rhs).swap(*this);
        return *this;
    }

    template<typename T>
    Any& operator=(const T& rhs)
    {
        Any(rhs).swap(*this);
        return *this;
    }

    bool empty() const { return bool(content_); }

    void clear() { Any().swap(*this); }

    const std::type_info& type() const
    {
        return content_ ? content_->type() : typeid(void);
    }

public:

    class placeholder
    {
    public:

        virtual ~placeholder() = default;

        std::shared_ptr<placeholder> clone() const
        {
            return clone_impl();
        }

        virtual const std::type_info& type() const = 0;

    private:

        virtual std::shared_ptr<placeholder> clone_impl() const = 0;
    };

    template<typename T>
    class holder : public placeholder
    {
    public:

        holder(const T& value) : value_(value) {}

        std::shared_ptr<holder> clone() const
        {
            return std::static_pointer_cast<holder>(clone_impl());
        }

        const std::type_info& type() const override
        {
            return typeid(value_);
        }

    public:

        T value_;

    private:

        std::shared_ptr<placeholder> clone_impl() const override
        {
            return std::make_shared<holder>(value_);
        }
    };

private:

    template<typename T>
    friend T any_cast(Any& rhs);

    template<typename T>
    friend T any_cast(const Any& rhs);

private:

    std::shared_ptr<placeholder> content_;
};

template<typename T>
T any_cast(Any& rhs)
{
    return std::static_pointer_cast<Any::holder<T>>(rhs.content_)->value_;
}

template<typename T>
T any_cast(const Any& rhs)
{
    return any_cast<T>(const_cast<Any&>(rhs));
}

}

#endif // ANY_H
