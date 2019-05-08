
A easy c++11 mongodb library,depend on mongoc,And no boost!!!!

Only header files!!!

Support connection pool!!!

Support Windows and Linux!!!

-------------------------------

#how to use

sudo apt-get install cmake libssl-dev libsasl2-dev
git clone https://github.com/nicehero/MongoHpp
cd EasyMongoHpp/dep
python build.py
cd ..
#show you the code
cat test.cpp

-------------------------------

how to test

./buildTest.sh
./test mongodb://user:pass@localhost:27017/?authSource=admin testdbname

welcome to my test c++11 server framework
https://gitee.com/nicehero/nicehero

nicehero.io