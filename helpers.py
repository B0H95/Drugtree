import sys

def list_selection(header, string_list):
    print(header)
    for i in range(len(string_list)):
        print(str(i) + ": " + string_list[i])
    try:
        selection = int(input())
        if selection < 0 or selection >= len(string_list):
            raise
        return selection
    except:
        print("Invalid input.")
        sys.exit(1)