import sys
from drugtree_database import DrugtreeDatabase
from helpers import list_selection

if __name__ == "__main__":
    database = DrugtreeDatabase()
    time_segments = database.get_time_segments()

    selected_time_segment_index = list_selection(
        "Select time_segment:",
        time_segments
    )

    time_segment = time_segments[selected_time_segment_index]
    time_segment_options = database.get_time_segment_options(time_segment)
    
    selected_option_index = list_selection(
        "Select option to activate:",
        time_segment_options
    )

    option = time_segment_options[selected_option_index]

    database.create_time_segment_record(time_segment, option)
    database.save_database()
    print("Success")
    sys.exit(0)