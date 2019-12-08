# **************************************************************
#  FILE NAME: api_commands_parser.py
#
#  MIT License
#
#  Copyright (c) 2019 Dylan Meng
#
#  For any Bug report, Feature request, Pull request,
# 	Positive criticism, and Donation.
#
#  Please visit: https://github.com/DylanMeng/Smart-D-LED-API
# 				 https://github.com/DylanMeng/Smart-D-LED-REMOTE
# 				 https://github.com/DylanMeng/Smart-D-LED-PCB
# 				 https://github.com/DylanMeng/Smart-D-LED-TOOLS
# 				 https://github.com/DylanMeng/Smart-D-LED-TOWER
#
#   Description: Transform api command to another language
#
#
#
# **************************************************************
import os
import re


class ApiCmdParser:

    def __init__(self):
        self.c_api_cmd_file = open(os.getcwd() + r"\api_commands.h", "r")
        self.b4a_api_cmd_file = open(os.getcwd() + r"\b4a_api_commands.bas", "wt")

    def to_b4a(self):
        """
            Parse example: from C to B4A:
            #define mFactoryReset  0x0100 --> Dim const mFactoryReset As String = "0100"

        :return:
        """
        regex = re.compile(r'0x[0-9A-Fa-f]{4}', re.IGNORECASE)  # Get 0x0000, 0xffff, 0xXXXX ...

        for line in self.c_api_cmd_file:
            final_line = ""
            if "#define" in line:
                pre_line = (line.replace("#define", "Dim const"))
                hex_code = regex.findall(pre_line)[0].replace("0x", "")
                final_line = regex.sub("As String = \"{}\"".format(hex_code), pre_line)
                final_line = final_line.replace("//", "\'")
                self.b4a_api_cmd_file.write(final_line)
            elif line in ['\n', '\r\n']:
                self.b4a_api_cmd_file.write(line)
            else:
                self.b4a_api_cmd_file.write("\'" + line)

            print(final_line)

        self.b4a_api_cmd_file.close()


if __name__ == '__main__':
    api_parser = ApiCmdParser()
    api_parser.to_b4a()
    print(api_parser.c_api_cmd_file.read())


