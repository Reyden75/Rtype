#ifndef __SPARSE_ARRAY__
#define __SPARSE_ARRAY__

#include <any>
#include <iostream>
#include <optional>
#include <vector>

template <typename Component>
class sparse_array {
  public:
    using value_type = std::optional<Component>;
    using reference_type = value_type &;
    using const_reference_type = value_type const &;
    using container_t = std::vector<value_type>;
    using size_type = typename container_t::size_type;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;

  public:
    sparse_array() : _data(container_t()){};

    sparse_array(sparse_array const &sparse_array)
        : _data(std::move(sparse_array._data)){};
    sparse_array(sparse_array &&sparse_array) noexcept
        : _data(std::move(sparse_array._data)){};
    ~sparse_array(){};

    sparse_array &operator=(sparse_array const &sparse_array)
    {
        return *this;
    };
    sparse_array &operator=(sparse_array &&sparse_array) noexcept
    {
        std::swap(_data, sparse_array._data);
        return *this;
    };

    friend std::ostream &operator<<(
        std::ostream &o, sparse_array const &sparse_array)
    {
        for (const_reference_type data : sparse_array._data)
            if (data.has_value())
                o << typeid(data.value()).name() << ", ";
            else
                o << "null"
                  << "\t";
        return o;
    };

    reference_type operator[](size_t idx)
    {
        return _data.at(idx);
    };

    const_reference_type operator[](size_t idx) const
    {
        return _data.at(idx);
    };

    iterator begin()
    {
        return _data.begin();
    };
    const_iterator begin() const
    {
        return _data.begin();
    };
    const_iterator cbegin() const
    {
        return _data.cbegin();
    };

    iterator end()
    {
        return _data.end();
    };
    const_iterator end() const
    {
        return _data.end();
    };
    const_iterator cend() const
    {
        return _data.cend();
    };

    size_type size() const
    {
        return _data.size();
    };

    reference_type insert_at(size_type position, Component const &component)
    {
        if (position >= this->size()) {
            _data.resize(position + 1);
        } else if (_data.at(position).has_value()) {
            _data.at(position).reset();
        }
        _data.at(position) = std::make_optional(component);
        return _data.at(position);
    };
    reference_type insert_at(size_type position, Component &&component)
    {
        if (position >= this->size()) {
            _data.resize(position + 1);
        }
        if (_data.at(position).has_value()) {
            _data.at(position).reset();
        }
        _data.at(position) = std::move(std::make_optional(component));
        return _data.at(position);
    };

    template <class... Params>
    reference_type emplace_at(size_type position, Params &&...params)
    {
        if (position >= this->size()) {
            _data.resize(position + 1);
        }
        if (_data.at(position).has_value()) {
            _data.at(position).reset();
        }
        _data.at(position) =
            std::move(std::make_optional<Component>(params...));
        return _data.at(position);
    };

    void erase(size_type position)
    {
        _data.at(position).reset();
    };

    size_type get_index(value_type const &component) const
    {
        unsigned int idx = 0;
        for (const_reference_type data : _data) {
            if (data.has_value()) {
                if (std::addressof(data) == std::addressof(component)) {
                    return idx;
                }
            }
            idx++;
        }
        return 0;
    };

  private:
    container_t _data;
};

#endif /* __SPARSE_ARRAY__ */