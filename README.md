# Gimme a date!
In Siobhan Roberts' biography of John Conway, she mentions his Doomsday algorithm and, with his plan to double his speed every 5 year, he had a computer program, which he called "GAD", written to test him.
It also mentions that John set up his computer so that when he logged on he was presented with ten random dates which he had to answer.   This is a reimplementation of this program in C++. 

## Building
This uses cmake and boost. It also uses Howard Hinnant's date library, but this is included as a submodule. So assuming you have cmake, a suitable c++ compiler and boost libraries installed you can build with

```
git clone https://github.com/andrewparr/gad.git
cd gad
mkdir build
cd build
cmake ..
make -j
```

## Usage
The program supports the following command line options
```
Options::
  -h [ --help ]           Display this help
  -n arg                  number of dates to test
  -s [ --start_date ] arg The random date will not be earlier than this date.
  -e [ --end_date ] arg   The random date will be before this date.
```

## Set up
If you want to set this up to run when you log in.
Edit your `~/.profile` file and add the following at the end
```
~/gad/build/bin/gad
retVal=$?
if [ $retVal -eq 1 ]; then
    echo "FAILED"
    exit
fi
```

Warning:  This will prevent you from logging in if you enter an incorrect day.  So you might want to ensure you have another account you can log in with should you need to.
