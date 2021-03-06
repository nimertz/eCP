import argparse

CLI=argparse.ArgumentParser()
CLI.add_argument(
  "--files",
  nargs="*",
  type=str,
  default=[],
  help="files to merge into single file"
)
CLI.add_argument(
  "--out",
  nargs="*",
  type=str,
  default=[],
  help="output file"
)

def main(files):
    contents = ""
    includes = []

    for file in args.files:
        with open(f'{file}', 'r') as f:
            contents = contents + f'//------------------------------{file}------------------------------\n'

            for line in f:
                #we do not care about #pragma once
                if (line.startswith('#pragma once')):
                    continue

                #only include '#include' statements if it has not been seen before
                if (line.startswith('#include')):
                    if (line not in includes):
                        includes.append(line)

                #it's a normal line, include it
                else:
                    contents = contents + line
            contents += "\n"

    #write everything to the new file
    with open(args.out[0], 'w+') as f:
        #file is .hpp
        if ('.hpp' in args.out[0]):
            f.write('#pragma once\n')

            #we do not want any include statements in the combined header
            for incl in includes:
                if ('.hpp' in incl):
                    continue

                f.write(incl)               

        else:
        #file is .cpp, include the combined header
            f.write('#include \"combined.hpp\"')

        #write everything else
        f.write("\n")
        f.write(contents)

args = CLI.parse_args()
main(args.files)