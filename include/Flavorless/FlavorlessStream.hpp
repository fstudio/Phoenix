/*********************************************************************************************************
* FlavorlessStream.hpp
* Note: Phoenix Flavorless Library
* Date: @2015.04
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef FLAVORLESS_STREAM_HPP
#define FLAVORLESS_STREAM_HPP
#include <fstream>

namespace Flavor{

#if defined(_MSC_VER) && _MSC_VER <= 1800
#define noexcept
# endif
template<typename CharType,typename Traits>
    class basic_filebuf : public std::basic_filebuf<CharType,Traits>
    {
    public:
        typedef std::basic_filebuf<CharType,Traits> my_base_type;
        basic_filebuf *open(char const *s,std::ios_base::openmode mode){
            return static_cast<basic_filebuf*>(
                my_base_type::open(Encoding::ToWide(s).c_str(), mode));
        }
    };

  template<typename CharType,typename Traits = std::char_traits<CharType> >
  class basic_ifstream : public std::basic_istream<CharType,Traits>
  {
  public:
    typedef basic_filebuf<CharType,Traits> internal_buffer_type;
    typedef std::basic_istream<CharType,Traits> internal_stream_type;

    basic_ifstream() : internal_stream_type(new internal_buffer_type())
    {
      buf_ = static_cast<internal_buffer_type *>(internal_stream_type::rdbuf());
    }
    explicit basic_ifstream(char const *file_name,
                            std::ios_base::openmode mode = std::ios_base::in)
      : internal_stream_type(new internal_buffer_type())
    {
      buf_ = static_cast<internal_buffer_type *>(internal_stream_type::rdbuf());
      open(file_name,mode);
    }
    void open(char const *file_name,std::ios_base::openmode mode = std::ios_base::in)
    {
      if(!buf_->open(file_name,mode | std::ios_base::in))
        {
        this->setstate(std::ios_base::failbit);
        }
      else
        {
        this->clear();
        }
    }
    bool is_open()
    {
      return buf_->is_open();
    }
    bool is_open() const
    {
      return buf_->is_open();
    }
    void close()
    {
      if(!buf_->close())
        {
        this->setstate(std::ios_base::failbit);
        }
      else
      {
        this->clear();
      }
    }

    internal_buffer_type *rdbuf() const
    {
      return buf_;
    }

    ~basic_ifstream() noexcept
    {
      buf_->close();
      delete buf_;
    }

  private:
    internal_buffer_type* buf_;
};

template<typename CharType,typename Traits = std::char_traits<CharType> >
class basic_ofstream : public std::basic_ostream<CharType,Traits>
{
  public:
  typedef basic_filebuf<CharType,Traits> internal_buffer_type;
  typedef std::basic_ostream<CharType,Traits> internal_stream_type;

  basic_ofstream() : internal_stream_type(new internal_buffer_type())
  {
  buf_ = static_cast<internal_buffer_type *>(internal_stream_type::rdbuf());
  }
  explicit basic_ofstream(char const *file_name,std::ios_base::openmode mode = std::ios_base::out) :
  internal_stream_type(new internal_buffer_type())
  {
    buf_ = static_cast<internal_buffer_type *>(internal_stream_type::rdbuf());
    open(file_name,mode);
  }
  void open(char const *file_name,std::ios_base::openmode mode = std::ios_base::out)
  {
    if(!buf_->open(file_name,mode | std::ios_base::out))
    {
    this->setstate(std::ios_base::failbit);
    }
    else
    {
    this->clear();
    }
  }
  bool is_open()
  {
    return buf_->is_open();
  }
  bool is_open() const
  {
    return buf_->is_open();
  }
  void close()
  {
    if(!buf_->close())
      {
      this->setstate(std::ios_base::failbit);
      }
    else
      {
      this->clear();
      }
  }

  internal_buffer_type *rdbuf() const
  {
    return buf_.get();
  }
  ~basic_ofstream() noexcept
  {
    buf_->close();
    delete buf_;
  }

  private:
  internal_buffer_type* buf_;
};

typedef basic_ifstream<char> ifstream;
typedef basic_ifstream<wchar_t> wifstream;
typedef basic_ofstream<char> ofstream;
typedef basic_ofstream<wchar_t> wofstream;


enum BOM
{
    BOM_None,
    BOM_UTF8,
    BOM_UTF16BE,
    BOM_UTF16LE,
    BOM_UTF32BE,
    BOM_UTF32LE
};

    // Read a BOM, if one exists.
    // If a BOM exists, the stream is advanced to after the BOM.
    // This function requires a seekable stream (but not a relative
    // seekable stream).
    inline BOM ReadBOM(std::istream& in)
    {
          if(!in.good())
    {
    return BOM_None;
    }
  unsigned long orig = in.tellg();
  unsigned char bom[4];
  in.read(reinterpret_cast<char*>(bom), 2);
  if(!in.good())
    {
    in.seekg(orig);
    return BOM_None;
    }
  if(bom[0] == 0xEF && bom[1] == 0xBB)
    {
    in.read(reinterpret_cast<char*>(bom+2), 1);
    if(in.good() && bom[2] == 0xBF)
      {
      return BOM_UTF8;
      }
    }
  else if(bom[0] == 0xFE && bom[1] == 0xFF)
    {
    return BOM_UTF16BE;
    }
  else if(bom[0] == 0x00 && bom[1] == 0x00)
    {
    in.read(reinterpret_cast<char*>(bom+2), 2);
    if(in.good() && bom[2] == 0xFE && bom[3] == 0xFF)
      {
      return BOM_UTF32BE;
      }
    }
  else if(bom[0] == 0xFF && bom[1] == 0xFE)
    {
    unsigned long p = in.tellg();
    in.read(reinterpret_cast<char*>(bom+2), 2);
    if(in.good() && bom[2] == 0x00 && bom[3] == 0x00)
      {
      return BOM_UTF32LE;
      }
    in.seekg(p);
    return BOM_UTF16LE;
    }
  in.seekg(orig);

    }

}
}

#endif
