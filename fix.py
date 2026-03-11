import codecs

path = r'invis/core/main/other.hpp'
try:
    with codecs.open(path, 'r', encoding='windows-1251', errors='ignore') as f:
        text = f.read()

    to_replace = "void validatemanipulatorpos(float maxxzmanipulator, float maxymanipulator)\r\n{"
    replacement = "void validatemanipulatorpos(float maxxzmanipulator, float maxymanipulator)\r\n{\r\n\tif (target_ply == nullptr) return;"
    
    # Alternatively try \n if \r\n is not present
    if to_replace not in text:
        to_replace = "void validatemanipulatorpos(float maxxzmanipulator, float maxymanipulator)\n{"
        replacement = "void validatemanipulatorpos(float maxxzmanipulator, float maxymanipulator)\n{\n\tif (target_ply == nullptr) return;"

    if to_replace in text:
        text = text.replace(to_replace, replacement)
        with codecs.open(path, 'w', encoding='utf-8-sig') as f:
            f.write(text)
        print("Success")
    else:
        print("String not found")

except Exception as e:
    print(e)
