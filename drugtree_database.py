import sys
import datetime

class DrugtreeDatabase:
    database = None
    database_path = None
    def __init__(self):
        if self.database == None:
            try:
                with open("DatabasePath", "r") as database_path_file:
                    self.database_path = database_path_file.readlines()[0]
                    self.database_path = self.database_path.strip()
                    with open(self.database_path, "r") as database:
                        self.database = database.readlines()
            except:
                print("Could not initialize DrugtreeDatabase.")
                sys.exit(1)
            self.__clean_database()
            self.__deserialize_database()

    def save_database(self):
        try:
            with open(self.database_path, "w") as db:
                db.write(self.__serialize_record(self.database[0]))
                for record in self.database[1:]:
                    db.write("\n" + self.__serialize_record(record))
        except:
            print("Could not open database.")
            sys.exit(1)

    def get_time_segments(self):
        return_list = []
        for record in self.database:
            if record["operation"] == "create" and record["parameters"][0] == "time_segment":
                return_list.append(record["parameters"][1])
        return return_list

    def get_time_segment_options(self, time_segment):
        for record in self.database:
            if record["operation"] == "create" and record["parameters"][0] == "time_segment" and record["parameters"][1] == time_segment:
                return record["parameters"][2:]
        print("time_segment " + time_segment + " did not exist.")
        sys.exit(1)

    def get_events(self):
        return_list = []
        for record in self.database:
            if record["operation"] == "create" and record["parameters"][0] == "event":
                return_list.append(record["parameters"][1])
        return return_list

    def create_event_record(self, event):
        time = self.__get_current_time()
        self.database.append({
            "time": time,
            "operation": "add",
            "parameters": [event]
        })

    def create_time_segment_record(self, time_segment, option):
        time = self.__get_current_time()
        self.database.append({
            "time": time,
            "operation": "add",
            "parameters": [time_segment, option]
        })

    def __clean_database(self):
        while len(self.database[len(self.database) - 1].strip()) == 0:
            self.database = self.database[:-1]
        for i in range(len(self.database)):
            self.database[i] = self.database[i].strip()

    def __deserialize_record(self, record):
        words = record.split()
        return {
            "time": {
                "year": int(words[0]),
                "month": int(words[1]),
                "day": int(words[2]),
                "hour": int(words[3]),
                "minute": int(words[4]),
                "second": int(words[5])
            },
            "operation": words[6],
            "parameters": words[7:]
        }

    def __deserialize_database(self):
        for i in range(len(self.database)):
            self.database[i] = self.__deserialize_record(self.database[i])

    def __serialize_record(self, record):
        entry = str(record["time"]["year"]) + " "
        entry += str(record["time"]["month"]) + " "
        entry += str(record["time"]["day"]) + " "
        entry += str(record["time"]["hour"]) + " "
        entry += str(record["time"]["minute"]) + " "
        entry += str(record["time"]["second"]) + " "
        entry += record["operation"] + " "
        entry += " ".join(record["parameters"])
        return entry

    def __get_current_time(self):
        now = datetime.datetime.now()
        return {
            "year": now.year,
            "month": now.month,
            "day": now.day,
            "hour": now.hour,
            "minute": now.minute,
            "second": now.second
        }