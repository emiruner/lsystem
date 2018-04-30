#
# Simple script to generate some code for Token
#

def stripAll(tokens):
  stripped = []
  
  for token in tokens:
    stripped.append(token.strip())
    
  return stripped

def genTokenCode(out, tokens):
  out.write("/**\n");
  out.write(" * This file is part of the LSys.\n");
  out.write(" *\n");
  out.write(" * Copyright (C) 2010, Emir Uner\n");
  out.write(" */\n");
  out.write("\n");
  out.write("#ifndef LSYS_MACHINEDESC_TOKENTYPE_HPP_INCLUDED\n");
  out.write("#define LSYS_MACHINEDESC_TOKENTYPE_HPP_INCLUDED\n");
  out.write("\n");
  out.write("namespace lsys\n")
  out.write("{\n")
  out.write("\n")
  out.write("namespace machinedesc\n")
  out.write("{\n")
  out.write("\n")
  out.write("namespace TokenType\n")
  out.write("{\n")
  out.write("    enum type\n")
  out.write("    {\n")
  for token in tokens:
    out.write ("        %s,\n" % token)
  out.write("    };\n")
  out.write("\n")
  out.write("    inline char const* toStr(type t)\n")
  out.write("    {\n")
  out.write("        switch(t)\n")
  out.write("        {\n")
  for token in tokens:
    out.write ("            case %s: return \"%s\";\n" % (token, token))
  out.write("            default: return \"<INVALID TOKEN TYPE>\";\n")
  out.write("        }\n")
  out.write("    }\n")
  out.write("}\n")
  out.write("\n")
  out.write("}\n")
  out.write("\n")
  out.write("}\n")
  out.write("\n")
  out.write("#endif\n")
  
def genTestCode(out, token):
    out.write("    inline bool is%s() const\n" % token)
    out.write("    {\n")
    out.write("        return TokenType::%s == type_;\n" % token);
    out.write("    }\n")
    out.write("\n")
    
f = open("tokens.txt")
tokenNames = stripAll(f.readlines())

with open("TokenType.hpp", "w") as ttf:
  genTokenCode(ttf, tokenNames)
  
with open("Token.gen.hpp", "w") as tgf:
  for token in tokenNames:
    genTestCode(tgf, token)
