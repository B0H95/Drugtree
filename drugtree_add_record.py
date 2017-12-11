import sys
import datetime

def open_database():
    try:
        with open("DatabasePath", "r") as database_path_file:
            database_path = database_path_file.readlines()[0]
            database_path = database_path.strip()
            with open(database_path, "r") as database:
                return database.readlines()
    except:
        print("Could not open database.")
        sys.exit(1)

def clean_database(database):
    while len(database[len(database) - 1].strip()) == 0:
        database = database[:-1]
    for i in range(len(database)):
        database[i] = database[i].strip()
    return database

def parse_database_entry(entry):
    words = entry.split()
    return {
        "time": {
            "year": words[0],
            "month": words[1],
            "day": words[2],
            "hour": words[3],
            "minute": words[4],
            "second": words[5]
        },
        "operation": words[6],
        "parameters": words[7:]
    }

def get_time_segments(database):
    time_segments = []
    for e in database:
        entry = parse_database_entry(e)
        if entry["operation"] == "create" and entry["parameters"][0] == "time_segment":
            time_segments.append(entry)
    return time_segments

def get_current_time():
    now = datetime.datetime.now()
    return {
        "year": now.year,
        "month": now.month,
        "day": now.day,
        "hour": now.hour,
        "minute": now.minute,
        "second": now.second
    }

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

def create_time_segment_entry(time_segment, option):
    time = get_current_time()
    entry = str(time["year"]) + " "
    entry += str(time["month"]) + " "
    entry += str(time["day"]) + " "
    entry += str(time["hour"]) + " "
    entry += str(time["minute"]) + " "
    entry += str(time["second"]) + " "
    entry += "add " + time_segment + " " + option
    return entry

def save_database(database):
    try:
        with open("DatabasePath", "r") as database_path_file:
            database_path = database_path_file.readlines()[0]
            database_path = database_path.strip()
            with open(database_path, "w") as db:
                return db.write("\n".join(database))
    except:
        print("Could not open database.")
        sys.exit(1)

if __name__ == "__main__":
    database = open_database()
    database = clean_database(database)
    time_segments = get_time_segments(database)

    selected_time_segment_index = list_selection(
        "Select time_segment:",
        list(map(lambda x: x["parameters"][1], time_segments))
    )

    time_segment = time_segments[selected_time_segment_index]
    time_segment_options = time_segment["parameters"][2:]
    
    selected_option_index = list_selection(
        "Select option to activate:",
        time_segment_options
    )

    new_entry = create_time_segment_entry(
        time_segment["parameters"][1],
        time_segment_options[selected_option_index]
    )

    database.append(new_entry)
    save_database(database)
    print("Success")
    sys.exit(0)