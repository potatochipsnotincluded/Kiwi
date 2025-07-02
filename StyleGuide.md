# Style Guide (MUST BE FOLLOWED)

1. Drop { onto new lines. There is an exeption
2. Don't drop { onto new lines for namespaces
3. For namespaces, leave an empty line at the start and end of the namespace eg:
```cpp
namespace Billy {

// code here
// code here

}
```
4. Capital letters for functions
5. Lower-case for normal variables.
6. Use m_Variable (capital first name letter), s_Variable (static, with capital first name letter), and for global inline variables, just use GlobalVariable, with capital first letter.
7. For global constants (constexpr, define, etc.), use SCREAMING_SNAKE_CASE
8. Give credit for borrowed code using a References commented page at the botton like this:
`// StackOverFlow, Retrieved 2025, https://suspicious_link.com`

And in the source code: `std::exit(-1); // (StackOverFlow, 2025)`
9. Use double-quote includes for files in the same project, and angle brackets for things outside the project.