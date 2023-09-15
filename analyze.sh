# Analyzes output simulation data

# Optional arguments:
# -v / --vis / --visualize  = Sets -a argument automatically, then after data analysis
#                             checks for an "output.root" file in the "output-files/analysis-gen"
#                             directory. If this file exists, it will be opened in the ROOT broswer

# If the output file directory is empty...
if ! [ -d "./output-files" ]
then
    # Print an appropriate error message and terminate
    echo -e "\nERROR: No output directory found. Unable to analyze data.\n"
    return
fi

# Get all needed command line arguments (ignore most)
IGNORE_NEXT=""
GET_ITERATIONS=""
ITERATIONS=""
VIS=""
for arg in "$@"
do
    if [ "$IGNORE_NEXT" == "SET" ]
    then
    	IGNORE_NEXT=""
    	continue
    fi
    if [ "$GET_ITERATIONS" == "SET" ]
    then
        GET_ITERATIONS=""
        re='^[0-9]+$'
        if ! [[ $arg =~ $re ]]
        then
            ERROR="SET"
            echo "ERROR: Invalid numerical value \"$arg\" found"
        else
           ITERATIONS=$(($arg))
        fi
        continue
    fi
    case $arg in
    	-rb|--rebuild) continue      
        ;;
        -v|--vis|--visualize) VIS="SET"
        ;;
        -a|--auto--|automatic) continue
        ;;
        -m|--macro) continue
        ;;
        -M|--MACRO) IGNORE_NEXT="SET"
        ;;
        -i|--iterations) GET_ITERATIONS="SET"
        ;;
        *) ERROR="SET"
           echo "ERROR: Invalid argument \"$arg\" found"
        ;;
    esac
done

# If there were any invalid arguments do not continue
if [ "$ERROR" == "SET" ]
then
    return
fi

if [ "$ITERATIONS" = "" ]
then
    ITERATIONS=1
fi

# If there is not a python program named "process-data.py" in the project directory...
if ! [ -f "process-data.cc" ]
then
    # Print an appropriate error message and return
    echo -e "\nERROR: No \"process-data.cc\" file found. Restore \"process-data.cc\" or run manually.\n"
    return
fi

# Move to output file directory
cd output-files

for (( i=0; i<$ITERATIONS; i++ ))
do
    FILE_PATH="analysis-gen-$i"
    # If the analysis directory does not exist...
    if ! [ -d "$FILE_PATH" ]
    then
        # Create the directory
        mkdir $FILE_PATH
    fi
    # Move into the analysis directory
    cd $FILE_PATH
    
    # Run the python program
    root -q -l "../../process-data.cc($i)"
    
    if [ "$VIS" == "SET" ]
    then
        # If the python program generated a .root file...
        if [ -f "output.root" ]
        then
            # Open the .root file in the root browser
            rootbrowse output.root
        else
            # Otherwise, print an appropriate error message
            echo "\nERROR: Unable to visualize data. Generated file \"output.root\" not found.\n"
        fi
    fi
    
    # Move back to the output file directory
    cd ..
    
    # If the analysis directory is empty...
    if [ -z "$(ls -A ./$FILE_PATH)" ]
    then
        # Remove the directory
        rm -r $FILE_PATH
    fi
done

# Move back to the main program directory
cd ..
