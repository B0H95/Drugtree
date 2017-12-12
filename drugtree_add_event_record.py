import sys
from drugtree_database import DrugtreeDatabase
from helpers import list_selection

if __name__ == "__main__":
    database = DrugtreeDatabase()
    events = database.get_events()

    selected_event_index = list_selection(
        "Select event:",
        events
    )

    event = events[selected_event_index]

    database.create_event_record(event)
    database.save_database()
    print("Success")
    sys.exit(0)