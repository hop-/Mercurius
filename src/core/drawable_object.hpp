#ifndef _CORE_DRAWABLE_OBJECT_HPP_
#define _CORE_DRAWABLE_OBJECT_HPP_

#include "rectangle.hpp"

namespace Core
{

class DrawableObject
{
private:
    const std::string m_path;
    unsigned m_width;
    unsigned m_height;
    unsigned m_rows;
    unsigned m_columns;

public:
    /**
     * @brief Base class for drawable object
     * @param p path to the texture
     * @param w widht of texture
     * @param h height of texture
     * @param r numbers of rows in texture, by default is 1
     * @param r numbers of columns in texture, by default is 1
     */
    DrawableObject(const std::string& p,
                   unsigned w, unsigned h,
                   unsigned r = 1, unsigned c = 1);

public:
    /// Return width of the texture
    unsigned width() const;

    /// Return height of the texture
    unsigned height() const;

    /// Return numbers of row
    unsigned rows() const;

    /// Return numbers of columns
    unsigned columns() const;

public:
    /**
     * @brief Return rectangle of passed state
     * @param s state id
     * @pre s <= rows() * columns(), s != 0
     */
    Rectangle rectForState(unsigned s) const;

};

} // end of namespace Core

#endif // _CORE_DRAWABLE_OBJECT_HPP_
