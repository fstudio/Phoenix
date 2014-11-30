mjson
=====
Another JSON library for C++, just what the world needed.

Building
--------
You can build mjson with CMake! 

**Linux, OSX, Unix**

    cmake -G "Unix Makefiles"
    make
    make install

Testing
-------
The test directory contains a CMake project for unit testing. mjson uses the Google C++ Testing Framewrk to run unit tests. The CMake project takes care of downloading and building with Google Test. Follow the steps above to build the unit tests.
   
Sample Usage
------------
**Including**

    #include <mjson.hpp>

**Parsing**

```C++
Parser parser;
Value outValue;
vector<string> errors;
if(!parser.Parse("{ 'foo' : 'bar' }", &outValue))
{
    errors = parser.GetErrors();
}
```

**Values**

```C++
Value answerToLife(42);
Value rootObject;
rootObject.SetValueForKey("Common Programmer Easter Egg", answerToLife);
string jsonString = rootObject.ToJSONString();
```
In this example, jsonString will contain `{"Common Programmer Easter Egg":42}`.

RTFM
----
Run doxygen to generate documentation.

OMG BUGS
--------
Please feel free to create issues.

