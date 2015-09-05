'''
Generate a C++ include file that can be used for type-safe numerical
computation with units.  Run with the -h option to get a manpage printed
to stdout.
'''

import sys, getopt, os
from string import join

out = sys.stdout.write
err = sys.stderr.write

# Keys and map used to store strings used in output
Units       = "Units"
fundamental = "Fundamental"
derived     = "Derived"
header      = "header"
trailer     = "trailer"
constant    = "Constant"
constants   = "constants"
typedefs    = "typedefs"
typedefs_derived = "typedefs_derived"
needed_includes  = "needed_includes"
parameters  = "Parameters"
outstream   = "OUTSTREAM"
f_unit      = "Unit"
d_unit      = "DerivedUnit"
include_file_default_name = "IncludeDefaultFileName"
include_file_name = "IncludeFileName"
units_class       = "UnitsClass"
units_namespace   = "UnitsNamespace"
numerical_type    = "NumericalType"
class_identifier  = "class_identifier"

output_strings = {
    Units       : {},
    fundamental : [],
    derived     : [],
    constant    : [],
    header      : "",
    trailer     : "",
    include_file_default_name : "unitscpp.h",
    include_file_name : "",
    units_class : "Units",
    units_namespace: "",
    numerical_type: "double",
    class_identifier: "class",  # Gets around bug in ctags 5.7
    needed_includes: '''
#include <ostream>
#include <sstream>
#include <string>
'''

}

# Other string constants
header_begin = "HeaderBegin"
header_end = "HeaderEnd"
trailer_begin = "TrailerBegin"
trailer_end = "TrailerEnd"
unit_marker_begin = "\"<\" "
unit_marker_end   = "\">\""
indent = "    "
nl = "\n"

# Settings from command line
si = 0     # If true, include SI units before user's units

manpage = '''Usage:  %(name)s [options] [configuration_file]

  Writes an include file that can be used for type-safe numerical
  computations with units.  The configuration_file controls the contents
  of the include file, including such things as:
        * The fundamental number of dimensions
        * The names of each dimension (e.g., Length, Mass, etc.)
        * The symbols to be used for the constants
  Note that each unit winds up being a C++ type; the compiler won't let
  you mix them except in specified ways.  This will help you make your
  numerical calculations type-safe.

  Options

    -e      Causes an empty configuration file to be written to stdout.
            This will contain comments on how to construct the configuration
            file.

    -s      Causes the 7 fundamental SI units to be added to the output.
'''

configuration_file_contents = '''# Empty configuration file for C++ units include file generation.  The
# method is based on the ideas in Barton and Nackman, "Scientific and
# Engineering C++", Addison-Wesley, 1994, ISBN 0201533936.  Also see
# W. Brown, "Applied Template Metaprogramming in SIunits:  the Library
# of Unit-Based Computation", 2001 (you'll have to search the web for
# this reference).
#
# The tokens that you specify in this file must be legitimate C++
# identifiers; otherwise, your code won't compile.  Note that the
# program that generates the units include file does no checking of
# the names you use.
#
#----------------------------------------------------------------------
# Header text (these lines are optional)
#
# All of the text between HeaderBegin and HeaderEnd will be inserted
# unchanged into the include file.  Use this for arbitrary preprocessor 
# code and C++ code.  Example:
#
#   HeaderBegin
#       #include "boost/rational.hpp"
#       #ifdef DEBUG
#       #include "my_debug.h"
#       #endif
#   HeaderEnd
#
# Note:  if you use a namespace via UnitsNamespace (see below), your
# code added here will not be in the namespace (contrast this to the
# Trailer section).

HeaderBegin
HeaderEnd


#----------------------------------------------------------------------
# Basic settings (these lines are optional)
#
# IncludeFileName is the name of the include file that will be
#   created.  The program _will_ overwrite an existing file.  If you
#   do not specify a name, the include file information will be
#   written to stdout.
# UnitsClass is the name of the templated class used for the Units
#   type.  Defaults to 'Units'.
# UnitsNamespace is the namespace that all the code will be under.
#   If this is the empty string, no namespace will be generated.
# NumericalType is the type you plan to use for numerical
#   calculations.  Defaults to 'double'.  You may use any type
#   that has the appropriate semantics.

IncludeFileName     =
UnitsClass          = units
UnitsNamespace      =
NumericalType       = double

#----------------------------------------------------------------------
# Fundamental dimensions (these lines are required)
#
# This section determines the number and names of the fundamental
# unit dimensions.  Here's an example line that specifies length as a 
# fundamental unit:
#
#       Unit = Length
#
# 'Unit' is required, followed by an '=' character, then the type of
# the fundamental unit.
#
# This fundamental unit specification will create a type called Length
# with which you can declare variables.  You'll want to include in the
# Constants section below a line such as 
#
#       Constant const Length m = 1;
#
# to define the numerical magnitude of the fundamental base unit
# (here, the meter).
#
# This then lets you write variable definitions such as 
#
#   Length diameter = 2.3*m;
#
# In the Constants section below, you could also write lines such as
#
#   Constant const Length meter = 1;
#   Constant const Length metre = 1;
#
# which are effectively aliases of the fundamental base unit symbol.
# Thus, you don't have to worry about only having one symbol for a
# particular unit.
#
# You need at least one line containing a Unit statement.
#
# If you invoked the program with the -s option, you'll have the seven
# fundamental SI units defined for you.  This is a convenience so you
# don't have to define them here (but they'll show up in the include
# file). 


#----------------------------------------------------------------------
# Derived units (these lines are optional)
#
# Similar to the fundamental units section, this section lets you
# define derived units.  You must write the derived unit in terms of
# the following items:
#       Any fundamental unit
#       Any derived unit defined on a previous line
#       Using the binary operators of * or /
#       Parentheses
#       Raising to an integer power with ** or ^
#
# You may also write expressions such as '1/Length'.  Note this won't
# work for any other integer or floating point number.
#
# Examples:
#   DerivedUnit = Velocity = Length/Time
#   DerivedUnit = Acceleration = Velocity/Time
#   DerivedUnit = Force = Mass*Acceleration
#   DerivedUnit = Energy = Force*Length
#
# The following are equivalent:
#   DerivedUnit = Area = 1/(Length*Length)
#   DerivedUnit = Area = 1/Length^2
#   DerivedUnit = Area = 1/Length**2
#   DerivedUnit = Area = Length**(-2)
#
# Note:  Length**0 is the same as 1.


#----------------------------------------------------------------------
# Constants (these lines are optional)
#
# These lines specify verbatim code that will be inserted into the
# include file.  Here's an example that defines millimeters when the
# base unit of m has been defined:
#
#   Constant = const Length mm = m/1000;
#
# While you could add this verbatim code to the trailer section, using
# the Constant keyword documents things better and lets you e.g. grep
# for all your defined constants.
#
# You may omit the keyword const, which will mean you'll have a global
# variable whose value may be changed later.


#----------------------------------------------------------------------
# Trailer text (these lines are optional)
#
# All of the text between TrailerBegin and TrailerEnd will be inserted
# unchanged into the include file.  Use this for arbitrary code you
# want in the include file.  
#
# Note if you define a namespace via UnitsNamespace, your code added
# here _will_ be in the namespace.

TrailerBegin
TrailerEnd
'''

include_file = '''
typedef %(NumericalType)s NT;   // Number Type

template<%(IPAR)s>
%(class_identifier)s %(UnitsClass)s
{
    public:
        %(UnitsClass)s(NT value_=NT(0)) : value(value_) {}

        // This turns the class into a function object that allows
        // the user to easily get at the value.
        NT operator()() const { return value; }

        // Helper function to get a text representation of the
        // object's dimensions.  It is static because the
        // representation is known at compile time.
        static std::string dim(void)
        {
            std::stringstream s;
            s << %(OUTSTREAM)s;
            return s.str();
        }

        // Helper function for unit conversions.
        NT to(const %(UnitsClass)s & u) const
        {
            return value/u();
        }

        %(UnitsClass)s & operator=(const %(UnitsClass)s & rhs)
        {
            value = rhs();
            return *this;
        }

        // Arithmetic operators
        %(UnitsClass)s & operator+=(const %(UnitsClass)s & rhs)
        {
            value += rhs.value;
            return *this;
        }

        %(UnitsClass)s & operator-=(const %(UnitsClass)s & rhs)
        {
            value -= rhs.value;
            return *this;
        }

        Units & operator*=(const NT & rhs)
        {
            value *= rhs;
            return *this;
        }

        Units & operator/=(const NT & rhs)
        {
            value /= rhs;
            return *this;
        }

    private:
        NT value;
};

// Addition
template <%(IPAR)s>
const %(UNIT)s operator+(const %(UNIT)s & lhs, const %(UNIT)s & rhs)
{
    return %(UNIT)s(lhs() + rhs());
}

// Subtraction
template <%(IPAR)s>
const %(UNIT)s operator-(const %(UNIT)s & lhs, const %(UNIT)s & rhs)
{
    return %(UNIT)s(lhs() - rhs());
}

// Multiplication
template <%(IPAR)s>
const %(UNIT)s operator*(const NT & lhs, const %(UNIT)s & rhs)
{
    return %(UNIT)s(lhs*rhs());
}

template <%(IPAR)s>
const %(UNIT)s operator*(const %(UNIT)s & lhs, const NT & rhs)
{
    return rhs*lhs;
}

template <%(IPARmul)s>
const %(UnitsClass)s<%(PARaPb)s> operator*(const %(UnitsClass)s<%(PARa)s> & lhs, const %(UnitsClass)s<%(PARb)s> & rhs)
{
    return %(UnitsClass)s<%(PARaPb)s>(lhs()*rhs());
}

// Division
template <%(IPAR)s>
const %(UNIT)s operator/(const %(UNIT)s & lhs, const NT & rhs)
{
    return %(UNIT)s(lhs()/rhs);
}

template <%(IPAR)s>
const %(mUNIT)s operator/(const NT & lhs, const %(UNIT)s & rhs)
{
    return %(mUNIT)s(lhs/rhs());
}

template <%(IPARmul)s>
const %(UnitsClass)s<%(PARaMb)s> operator/(const %(UnitsClass)s<%(PARa)s> & lhs, const %(UnitsClass)s<%(PARb)s> & rhs)
{
    return %(UnitsClass)s<%(PARaMb)s>(lhs()/rhs());
}

// Comparisons and ordering
template <%(IPAR)s>
bool operator==(const %(UNIT)s & lhs, const %(UNIT)s & rhs)
{
    return (lhs() == rhs());
}

template <%(IPAR)s>
bool operator==(const %(UNIT)s & lhs, const NT & rhs)
{
    return (lhs() == rhs);
}

template <%(IPAR)s>
bool operator==(const NT & lhs, const %(UNIT)s & rhs)
{
    return (lhs == rhs());
}

template <%(IPAR)s>
bool operator!=(const %(UNIT)s & lhs, const %(UNIT)s & rhs)
{
    return not (lhs() == rhs());
}

template <%(IPAR)s>
bool operator!=(const %(UNIT)s & lhs, const NT & rhs)
{
    return not (lhs() == rhs);
}

template <%(IPAR)s>
bool operator!=(const NT & lhs, const %(UNIT)s & rhs)
{
    return not (lhs == rhs());
}


// Ordering
template <%(IPAR)s>
bool operator<=(const %(UNIT)s & lhs, const %(UNIT)s & rhs)
{
    return lhs() <= rhs();
}

template <%(IPAR)s>
bool operator<=(const %(UNIT)s & lhs, const NT & rhs)
{
    return (lhs() <= rhs);
}

template <%(IPAR)s>
bool operator<=(const NT & lhs, const %(UNIT)s & rhs)
{
    return (lhs <= rhs());
}


template <%(IPAR)s>
bool operator>=(const %(UNIT)s & lhs, const %(UNIT)s & rhs)
{
    return lhs() >= rhs();
}

template <%(IPAR)s>
bool operator>=(const %(UNIT)s & lhs, const NT & rhs)
{
    return (lhs() >= rhs);
}

template <%(IPAR)s>
bool operator>=(const NT & lhs, const %(UNIT)s & rhs)
{
    return (lhs >= rhs());
}


template <%(IPAR)s>
bool operator<(const %(UNIT)s & lhs, const %(UNIT)s & rhs)
{
    return lhs() < rhs();
}

template <%(IPAR)s>
bool operator<(const %(UNIT)s & lhs, const NT & rhs)
{
    return (lhs() < rhs);
}

template <%(IPAR)s>
bool operator<(const NT & lhs, const %(UNIT)s & rhs)
{
    return (lhs < rhs());
}


template <%(IPAR)s>
bool operator>(const %(UNIT)s & lhs, const %(UNIT)s & rhs)
{
    return lhs() > rhs();
}

template <%(IPAR)s>
bool operator>(const %(UNIT)s & lhs, const NT & rhs)
{
    return (lhs() > rhs);
}

template <%(IPAR)s>
bool operator>(const NT & lhs, const %(UNIT)s & rhs)
{
    return (lhs > rhs());
}

template <%(IPAR)s>
std::ostream & operator<<(std::ostream & s, const %(UNIT)s & rhs)
{
    return s << rhs();
}
'''

class U:
    '''Perform dimension arithmetic for arbitrary units.  This class is
    used to calculate the fundamental unit expressions for derived units.
    '''
    def __init__(me, d):
        me.d = tuple(d)
    def __repr__(me):
        return "%s," % join(["%d" % int(i) for i in me.d], ",")
    def __mul__(me, b):
        return U([me.d[i] + b.d[i] for i in xrange(len(me.d))])
    def __div__(me, b):
        return U([me.d[i] - b.d[i] for i in xrange(len(me.d))])
    def __pow__(me, b):
        if (type(b) != type(0)) and (type(b) != type(0L)):
            raise TypeError("Bad exponent:  " + `b`)
        if b == 0: return U([0]*len(me.d))
        if b == 1:  return x
        if b < 0:
            x = U([-i for i in me.d])
            if b == -1:  return x
            for i in xrange(abs(b)-1): x /= me
        else:
            x = U(me.d)
            for i in xrange(b-1): x *= me
        return x

def ParseCommandLine():
    program_name = sys.argv[0]
    if len(sys.argv) < 2:
        out(manpage % {"name" : program_name})
        sys.exit(0)
    try:
        optlist, args = getopt.getopt(sys.argv[1:], "es")
    except getopt.error, str:
        err(str)
        sys.exit(1)
    for opt in optlist:
        if opt[0] == "-e":
            out(configuration_file_contents)
            sys.exit(0)
        if opt[0] == "-s":
            global si, output_strings
            si = 1
            output_strings[fundamental] = [ "Mass", "Length",
                "Time", "Current", "Temperature", "Quantity",
                "LuminousIntensity"]
    if len(args) != 1:
        Usage()
    return args[0]

def ReadConfigFile(config_file):
    try:
        lines = open(config_file).readlines()
    except:
        err("Error:  couldn't read config file '%s'%s" % (config_file, nl))
        sys.exit(1)
    return lines

def RemoveComments(lines):
    # Remove comments and empty lines by reading backwards through the file
    for ix in xrange(len(lines)-1, -1, -1):
        if not lines[ix].strip():
            del lines[ix]
            continue
        if lines[ix].strip()[0] == "#":
            del lines[ix]
    lines = [line.strip() for line in lines]
    return lines

def GetSection(lines, StartString, EndString):
    '''Find the text between lines with StartString and EndString on
    them.  Return the text between them and delete the associated lines
    from the lines list.
    '''
    StartString += nl  # The lines from the file have newlines at the end
    EndString += nl
    start = end = -1
    if StartString not in lines:
        if EndString in lines:
            err("Error:  Missing '%s' in config file%s" % (StartString, nl))
            sys.exit(1)
        return None
    if StartString in lines:
        start = lines.index(StartString)
        if EndString not in lines:
            err("Error:  Missing '%s' in config file%s" % (EndString, nl))
            sys.exit(1)
        end = lines.index(EndString)
        if start > end:
            err("Error:  '%s' comes before '%s' in config file%s" % \
                (EndString, StartString, nl))
            sys.exit(1)
    header = None
    if end - start > 1:
        header = lines[start+1:end]
    del lines[start:end+1]
    if header:
        return join(header, nl)
    else:
        return None

def Split(line, char="="):
    '''Split on the first indicated character.
    '''
    if char not in line:
        err("Error:  configuration file line missing '%s':%s%s%s" % 
            (char, nl, line, nl))
        sys.exit(1)
    position = line.find(char)
    key = line[:position].strip()
    value = line[position+1:].strip()
    return [key, value]

def ParseLine(line):
    '''Parse on the first '=' character on the line.
    '''
    if '=' not in line:
        err("Error:  configuration file line missing '=':%s%s%s" % 
            (nl, line, nl))
        sys.exit(1)
    position = line.find("=")
    key = line[:position].strip()
    value = line[position+1:].strip()
    return [key, value]

def ParseUnit(line, string):
    '''Make sure there's an '=' character and two tokens.
    '''
    if '=' not in string:
        err("Error:  configuration file line missing '=':%s%s%s" % 
            (nl, line, nl))
        sys.exit(1)
    name, symbol = Split(string, "=")
    return name + "=" + symbol

def ProcessLines(lines):
    '''Fill the output_strings global with the relevant information, 
    ready to be printed out to the include file.
    '''
    global output_strings
    AllowedKeys = (units_class, units_namespace, numerical_type, f_unit, 
        d_unit, constant, include_file_name)
    for line in lines:
        key, value = Split(line, "=")
        if key not in AllowedKeys:
            err("Error:  configuration file line with bad key '%s':%s%s%s" % 
                (key, nl, line, nl))
            sys.exit(1)
        if key == f_unit:
            output_strings[fundamental].append(value)
        elif key == d_unit:
            output_strings[derived].append(value)
        elif key == constant:
            output_strings[constant].append(value)
        else:
            output_strings[key] = value

def CheckData():
    # Check for duplicates in fundamental units.
    # Form is Unit = Length
    units = {}
    for name in output_strings[fundamental]:
        if units.has_key(name):
            err("Error:  '%s' is a duplicated fundamental unit%s" % (name, nl))
            sys.exit(1)
        else:
            units[name] = 0
    # Check for duplicates in derived units.
    # Form is DerivedUnit = Expression(fund. units, derived units)
    units = {}
    for item in output_strings[derived]:
        type, name = Split(item, "=")
        if units.has_key(type):
            err("Error:  '%s' is a duplicated derived unit%s" % (type, nl))
            sys.exit(1)
        else:
            units[type] = 0
    # Check for duplicates in constants units.
    # Form is Constant const Length mm = m/1000;
    units = {}
    for item in output_strings[constant]:
        if "=" not in item:
            err("Error:  constant '%s' is missing '='%s" % (item, nl))
            sys.exit(1)
        items = item.split()
        if len(items) < 4:
            err("Error:  constant '%s' is of improper form%s" % (item, nl))
            sys.exit(1)
        if items[0] == "const":
            key = items[2]
        else:
            key = items[1]
        if units.has_key(key):
            err("Error:  '%s' is a duplicated constant%s" % (key, nl))
            sys.exit(1)
        else:
            units[key] = 0

def MakeMap():
    '''Make a map that contains all the variables needed for outputting
    the include file.
    '''
    m = {}
    for key in output_strings[parameters]:
        m[key] = output_strings[parameters][key]
    m[numerical_type]   = output_strings[numerical_type]
    m[units_class]      = output_strings[units_class]
    m[outstream]        = output_strings[outstream]
    m[class_identifier] = output_strings[class_identifier]
    return m

def MakeTemplateParameters():
    def f(s, number_of_dimensions):
        string = range(1, number_of_dimensions + 1)
        string = [s % i for i in string]
        return join(string, ", ")
    def g(s, number_of_dimensions):
        string = range(1, number_of_dimensions + 1)
        string = [s % (i, i) for i in string]
        return join(string, ", ")
    global output_strings
    number_of_dimensions = len(output_strings[fundamental])
    d = {}
    d["PAR"]     = f("U%d", number_of_dimensions)
    d["PARa"]    = f("U%da", number_of_dimensions)
    d["PARb"]    = f("U%db", number_of_dimensions)
    d["MPAR"]    = f("-U%d", number_of_dimensions)
    d["IPAR"]    = f("int U%d", number_of_dimensions)
    d["IPARmul"] = f("int U%da", number_of_dimensions) + ", " + \
                   f("int U%db", number_of_dimensions)
    d["PARaPb"]  = g("U%da+U%db", number_of_dimensions)
    d["PARaMb"]  = g("U%da-U%db", number_of_dimensions)
    d["UNIT"]    = "%s<%s>" % (output_strings[units_class], d["PAR"])
    d["mUNIT"]    = "%s<%s>" % (output_strings[units_class], d["MPAR"])
    output_strings[parameters] = d

def BuildNeededStrings():
    global output_strings
    # String for dumping unit's dimensions
    number_of_dimensions = len(output_strings[fundamental])
    string = range(1, number_of_dimensions)
    string = ["<< U%d << \",\"" % i for i in string]
    string.append("<< U%d" % number_of_dimensions)
    s = unit_marker_begin + join(string) + " << " + unit_marker_end
    output_strings[outstream] = s
    # Build typedefs
    s = ""
    ns = output_strings[units_namespace]
    n = len(output_strings[fundamental])
    names_to_pos = {}  # Map dimension names to position for derived typedefs
    for ix in xrange(n):
        name = output_strings[fundamental][ix]
        tp = repr(output_strings[Units][name])
        if tp[-1] == ",": 
            tp = tp[:-1] # Remove comma
        if ns:
            s += "typedef %s::%s<%s> %s;%s" % \
                (ns, output_strings[units_class], tp, name, nl)
        else:
            s += "typedef %s<%s> %s;%s" % \
                (output_strings[units_class], tp, name, nl)
        names_to_pos[name] = ix + 1
    output_strings[typedefs] = s 
    # Build derived typedefs
    def Derived(derived_unit_string):
        name, expression = Split(derived_unit_string, "=")
        tp = repr(output_strings[Units][name])
        if tp[-1] == ",": 
            tp = tp[:-1] # Remove comma
        if ns:
            s = "typedef %s::%s<%s> %s;%s" % \
                (ns, output_strings[units_class], tp, name, nl)
        else:
            s = "typedef %s<%s> %s;%s" % \
                (output_strings[units_class], tp, name, nl)
        return s
    n = len(output_strings[derived])
    s = ""
    for item in output_strings[derived]:
        s += Derived(item)
    output_strings[typedefs_derived] = s
    # Build constants
    s = ""
    for string in output_strings[constant]:
        s += string + nl
    output_strings[constants] = s + nl

def WriteIncludeFile():
    s = output_strings[include_file_name]
    of = sys.stdout
    if s != "":
        # Note file will be overwritten if it is present
        of = open(s, "w")
    else:
        s = output_strings[include_file_default_name]
    out = of.write
    s = s.replace(".", "_")
    t = "#ifndef %s%s" % (s, nl)
    out(t)
    out("#define %s%s" % (s, nl))
    out(output_strings[needed_includes])
    if output_strings[header]:
        out(nl + "// From configuration file header" + nl)
        out(output_strings[header] + nl + nl)
    if output_strings[units_namespace]:
        out("namespace %s%s" % (output_strings[units_namespace], nl))
        out("{%s" % nl)
    out(include_file % MakeMap())
    out(nl + "// Typedefs for fundamental units" + nl)
    out(output_strings[typedefs])
    out(nl + "// Typedefs for derived units" + nl)
    out(output_strings[typedefs_derived])
    out(nl + "// Unit constants" + nl)
    out(output_strings[constants])
    if output_strings[trailer]:
        out("// From configuration file trailer" + nl)
        out(output_strings[trailer] + nl)
    if output_strings[units_namespace]:
        out("} // namespace %s%s%s" % (output_strings[units_namespace], nl, nl))
    out("#endif //" + t)
    if s:
        of.close()

def ConstructFundamentalUnits():
    '''Our basic procedure is to compile expressions that create the
    fundamental unit names objects in our local scope, then put the objects
    into the dictionary keyed by "Units" in the output_strings global 
    dictionary.  We'll use these to evaluate the expressions for derived
    units.
    '''
    global output_strings
    n = len(output_strings[fundamental])
    d = {}  # Dictionary for our fundamental objects
    for ix in xrange(n):
        name = output_strings[fundamental][ix]
        t = [0]*n
        t[ix] = 1
        # Construct the string to compile
        s = "%s = U((%s))" % (name, repr(U(t)))
        try:
            c = compile(s, "", "single")
            eval(c)  # Evaluate it in our local namespace
            # Get the object created and put into our dictionary
            d[name] = locals()[name]
        except:
            err("Fundamental unit '%s' has a problem.%s" % (name, nl))
            sys.exit(1)
    # Store into the global dictionary for use with evaluating derived
    # units.
    if len(d) == 0:
        err("Need at least one Unit statement in configuration file" + nl)
        sys.exit(1)
    output_strings[Units] = d

def ConstructDerivedUnits():
    '''The procedure here is analogous to what was done in
    ConstructFundamentalUnits, except we'll construct strings to be
    compile that contain the expressions the user put into the
    configuration file.  We'll then get the dimensions of the
    resulting unit, which is what we'll use later for the template
    parameters of the derived unit.  The beauty of this approach is
    that we use the python parser to evaluate the expressions and
    determine whether they are legitimate (i.e., we don't have to
    write a parser).  The U class captures the semantics of combining
    the units' dimensions.
    '''
    global output_strings
    num_fund = len(output_strings[fundamental])
    # First, put the fundamental units into our local namespace.  This
    # duplicates the work in ConstructFundamentalUnits(), but I wanted
    # to keep the tasks separate.
    for name in output_strings[Units]:
        try:
            s = "%s = U((%s))" % (name, output_strings[Units][name])
            c = compile(s, "", "single")
            eval(c)
        except:
            err("Internal error in ConstructDerivedUnits()" + nl)
            sys.exit(1)
    # Now evaluate the derived expressions
    n = len(output_strings[derived])
    d = output_strings[Units]  # Fundamental units are already here
    one = U([0]*num_fund)      # Allow things like '1/Length'
    for ix in xrange(n):
        name, expression = Split(output_strings[derived][ix], "=")
        if d.has_key(name):
            err("Derived unit '%s' is already the name of a unit.%s" % 
                (name, nl))
            sys.exit(1)
        # Construct the string to compile
        s = expression
        # Needed substitutions to make things work
        s = s.replace("1", "one")  # Allow things line '1/Length'
        s = s.replace("^", "**")   # Let's '^' be used for exponentiation
        try:
            c = compile(s, "", "eval")
            result = eval(c)
        except:
            err("Derived unit '%s' not a valid expression.%s" % (name, nl))
            sys.exit(1)
        d[name] = U(result.d)
        locals()[name] = d[name]
    output_strings[Units] = d

def main():
    config_file = ParseCommandLine()
    lines = ReadConfigFile(config_file)
    output_strings[header]  = GetSection(lines, header_begin, header_end)
    output_strings[trailer] = GetSection(lines, trailer_begin, trailer_end)
    RemoveComments(lines)
    ProcessLines(lines)
    CheckData()
    ConstructFundamentalUnits()
    ConstructDerivedUnits()
    BuildNeededStrings()
    MakeTemplateParameters()
    WriteIncludeFile()

main()
