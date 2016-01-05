#ifndef TOOL
#define TOOL
#include <vector>
#include "nicefonctor.h"
#include "globaltype.h"
/**
 * @file tool.h
 * \brief With Usage of Quantum Mecanic.
 * Smart Code to make smart code. Realy nice!! :-)
 * @author (binaire) Alexandre Wery
 */
/**
 *  \brief namespace global
 * All tool are into this
 *  @namespace binaire
 */
namespace binaire
{

    template<typename Fonctor = equalOP, typename X, typename Y>
    /**
     * \brief Find
     * Function to fin value into array
     * it's a template an need 3 argument
     *  - Fonctor : operator(A,A) to check the equality
     *  - X : type of value to find
     *  - Y : Type of Array
     * @param[in] val
     * looking value into arry
     * @param[in] Chaine
     * space of search
     * @param[in] pos
     * position where begin search
     * @return
     * return the position of the element find
     * if not find return size of array
     */
    uint_t Find(const X &val, const Y &Chaine, uint_t pos = 0)
    {
        Fonctor OP;
        while(pos < Chaine.size())
        {
            if(OP(Chaine[pos] ,val))
                break;
            ++pos;
        }
        return pos;
    } // Find

    /**
     *  @namespace binaire::experimental
     *  \brief namespace with all experimental tool like tab ref
     */
    namespace experimental {

        template<typename Obj, typename... Arg>
        /**
         * @class SignalObj tool.h
         * \brief The SignalObj class
         *
         * Class to link slots object Member
         * @todo mutex missing
         */
        class SignalObj
        {
        public:
            /**
             * @typedef ObjPtr
             * \brief ObjPtr
             * alias to Obj*
             */
            typedef Obj *ObjPtr;
            /**
             * @typedef func
             * \brief func
             * alias to function member
             */
            typedef void(Obj::*func)(Arg...);
            /**
             * \brief link
             * function to link signal to slot
             * @param[in] function
             * function slot to link to signalObj
             */
            void link(func function)
            {
                m_slot.push_back(function);
            } // link

            /**
             * \brief operator ()
             * signal caller function
             * @param ArgumentList
             * Argument of signal
             */
            void operator ()(Arg&&... ArgumentList)
            {
                for(func &function : m_slot)
                    m_ObjectBase->*function(ArgumentList...);
            } // operator ()

            /**
             * \brief setObjectBase
             * change object slot called by member
             * @param ObjectBase
             */
            void setObjectBase(ObjPtr ObjectBase)
            {
                m_ObjectBase = ObjectBase;
            } // setObjectBase


        private:
            std::vector<func> m_slot;
            ObjPtr m_ObjectBase;
        }; // SignalObj

        template<typename... Arg>
        /**
         * @class Signal tool.h
         * \brief The Signal template class
         */
        class Signal
        {
        public:
            /**
             * @typedef func
             * \brief func
             * alias to slot type
             */
            typedef void(func)(Arg...);
            /**
             * @typedef funcPtr
             * @brief funcPtr
             * alias to function pointer
             */
            typedef func *funcPtr;

            /**
             * \brief link
             * function to link signal to slot
             * @param[in] function
             * function slot to link to signalObj
             */
            void link(func *function)
            {
                m_slot.push_back(function);
            } // link

            /**
             * @brief unlink
             * unlink signal to slots
             * @param function
             */
            void unlink(func *function)
            {
                const uint_t pos(Find(function, m_slot));
                if(pos!=m_slot.size())
                    m_slot.erase(m_slot.begin() + pos);
            } // unlink

            /**
             * @brief operator +=
             * @see link
             * @param addFunction
             * @return
             */
            Signal &operator +=(funcPtr addFunction)
            {
                link(addFunction);
            }

            /**
             * @brief operator -=
             * @see unlink
             * @param addFunction
             * @return
             */
            Signal &operator -=(funcPtr addFunction)
            {
                unlink(addFunction);
            }

            /**
             * \brief operator ()
             * signal caller function
             * @param ArgumentList
             * Argument of signal
             */
            void operator ()(Arg&&... ArgumentList)
            {
                for(funcPtr function : m_slot)
                    function(ArgumentList...);
            } // operator ()
        private:
            std::vector<funcPtr> m_slot;
        }; // Signal

        template<typename... Arg>
        /**
         * \brief creatSignal
         * Function to creat Signal from slot
         * @param function
         * get function to
         * @return
         * creat Signal
         */
        Signal<Arg...> creatSignal(void(*function)(Arg...))
        {
            Signal<Arg...> SignalLinked;
            SignalLinked.link(function);
            return SignalLinked;
        }

        template<typename Obj, typename... Arg>
        /**
         * \brief creatSignal
         * Function to creat Signal Object from slot
         * @param function
         * get member of function
         * @param ptr
         * Object of member
         * @return
         * creat Signal Object
         */
        SignalObj<Obj, Arg...> creatSignal(void(Obj::*function)(Arg...), Obj *ptr)
        {
            SignalObj<Obj, Arg...> SignalLinked;
            SignalLinked.link(function);
            SignalLinked.setObjectBase(ptr);
            return SignalLinked;
        }

        template<typename TypeX, typename RemoverFunction = deletePtr>
        /**
         * @class AutoRemover
         * \brief The AutoRemover class
         * Class creat to delete pointer at the end of program
         */
        class AutoRemover
        {
        public:
            /**
              * \brief Destructor
              *
              * Destroy all pointer in the m_tabPtr
              */
            ~AutoRemover()
            {
                for(TypeX *&value : m_tabPtr)
                    deleter(value);
            }

            /**
             * \brief add
             * Add new ptr to destroy
             * @param Value
             * pointer to add in m_tabPtr
             */
            void add(TypeX *Value)
            { m_tabPtr.push_back(Value); }
            /**
             * \brief remove
             * Remove value in m_tabPtr
             * @param Value
             * pointer to remove
             */
            void remove(TypeX *Value)
            { for(uint_t i(0) ; i < m_tabPtr.size() ; ++i) if(m_tabPtr[i] == Value) { m_tabPtr.erase(m_tabPtr.begin() + i); break; }}

            /**
             * \brief size
             * fonction to get size of m_tabPtr
             * @return
             */
            uint_t size()
            { return m_tabPtr.size(); }

            /**
             * \brief get
             * get pointer in m_tabPtr at position i
             * @param i
             * indice of m_tabPtr
             * @return
             */
            TypeX *get(const uint_t &i)
            { return m_tabPtr[i]; }
        private:
            std::vector<TypeX *> m_tabPtr;
            RemoverFunction deleter;
        };

        template<typename Type>
        /**
         * @class RefElement
         * \brief The RefElement class
         * Object like reference to variable to be use like variable Type
         * Made with Quantum Mechanic
         */
        class RefElement
        {
        public:
            /**
             * \brief RefElement
             * default constructor
             */
            RefElement()
            {}
            /**
             * \brief RefElement
             * Constructor
             * @param val
             * Reference to value
             */
            RefElement(Type &val) : m_ptr(&val)
            {}
            /**
             * \brief RefElement
             * Constructor
             * @param val
             * pointer to value
             */
            RefElement(Type *val) : m_ptr(val)
            {}

            /**
             * \brief operator Type &
             * Quantum operator
             * like every cast to Type type
             */
            operator Type& ()
            {return *m_ptr;}

            /**
             * \brief operator Type *
             * Quantum operator
             * like every cast to Type* type
             */
            operator Type* ()
            {return m_ptr;}

            /**
             * \brief ptr
             * fonction to get pointer to value
             * @return
             */
            Type *ptr() const
            {
                return m_ptr;
            }

            /**
             * \brief value
             * function who return value reference
             * @return
             */
            Type &value() const
            {
                return *m_ptr;
            }

            /**
             * \brief value
             * function who return value reference
             * @return
             */
            Type &value()
            {
                return *m_ptr;
            }

            /**
             * \brief setPtr
             * function to change value pointer
             * @param ptr
             */
            void setPtr(Type &ptr)
            {
                m_ptr = &ptr;
            }

            /**
             * \brief setPtr
             * function to change value pointer
             * @param ptr
             */
            void setPtr(Type *ptr)
            {
                m_ptr = ptr;
            }

        private:
            Type *m_ptr = nullptr;
        };

        template<typename Type>
        /**
         * @class vectorRef
         * \brief The vectorRef class
         * Object to extract value by reference from arrays
         *
         */
        class vectorRef : public std::vector< RefElement<Type> >
        {
        public:
            /**
             * @typedef Element
             * \brief Element
             * representation of an element of Type
             */
            typedef RefElement<Type> Element;
            vectorRef()
            {}

            template<typename Tab>
            /**
             * \brief LineRef
             * Custum constructor to enable initialisation with all array like operator[]
             * @param TabLink
             * Array single dimension
             * @param x
             * begin offset in Array
             * @param width
             * size of array
             */
            vectorRef(Tab &TabLink, const uint_t &x, const uint_t &width)
            {
                this->resize(width);
                for(uint_t i(0) ; i<width ; ++i)
                    this->at(i).setPtr(TabLink[i+x]);
            }

            /**
             * \brief operator []
             * override operator[] to like class RefElement
             * @param n
             * offset element
             * @return
             */
            Type &operator [](const uint_t &n)
            {return this->at(n).value();}

            /**
             * \brief operator [] const
             * override operator[] to like class RefElement
             * @param n
             * offset element
             * @return
             */
            Type &operator [](const uint_t &n) const
            {return this->at(n).value();}

            template<typename Tab>
            /**
             * \brief setLineRef
             * function to reset to new array
             * @param TabLink
             * Array of value
             * @param x
             * offset where begin
             * @param width
             * new size of array
             */
            void setLineRef(Tab &TabLink, const uint_t &x, const uint_t &width)
            {
                this->resize(width);
                for(uint_t i(0) ; i<width ; ++i)
                    this->at(i).setPtr(TabLink[i+x]);
            }
        };

        template<typename Type>
        /**
         * @class BiDimvectorRef
         * \brief The BiDimvectorRef class
         * Object to extract element of arrays bi-dimensional
         */
        class BiDimvectorRef : public std::vector< vectorRef<Type> >
        {
        public:
            /**
             * @typedef TabLineRef
             * \brief TabLineRef
             * alias to Line of this arrays
             */
            typedef vectorRef<Type> TabLineRef;
            /**
             * \brief MatrixRef
             * Default Constructor
             */
            BiDimvectorRef()
            {}

            template<typename Tab>
            /**
             * \brief MatrixRef
             * Constuctor to fast usage
             * @param TabLink
             * Array of array element
             * @param x
             * offset of second array
             * @param y
             * offset of first array
             * @param heigh
             * size of first local array
             * @param width
             * size of second local array
             */
            BiDimvectorRef(Tab &TabLink, const uint_t &x, const uint_t &y, const uint_t &heigh, const uint_t &width)
            {
                this->resize(heigh);
                for(uint_t i(0) ; i<heigh ; ++i)
                    this->at(i).setLineRef(TabLink[y+i], x, width);
            }

            template<typename Tab>
            /**
         * \brief setTabRef
         * Reset to new frame array at (x, y) position and height and width size of array
         * @param TabLink
         * Array of array element
         * @param x
         * offset of second array
         * @param y
         * offset of first array
         * @param heigh
         * size of first local array
         * @param width
         * size of second local array
         */
            void setTabRef(Tab &TabLink, const uint_t &x, const uint_t &y, const uint_t &heigh, const uint_t &width)
            {
                this->resize(heigh);
                for(uint_t i(0) ; i<heigh ; ++i)
                    this->at(i).setLineRef(TabLink[y+i], x, width);
            }
        };
    }
}
#endif // TOOL
