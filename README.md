# Prime Number Generator

This is an prime number generator application where i have used C++ to generate prime number in the range and i have defined two algorithms in this and we can interact with the algorithms with the api by defining (start
, end, algorithm). I have used Node.js for the api and mongodb to store the data.

<hr>

I have used Napi (Node api) to create addon and with that we can connect c++ with node.js and interact with the functions of c++. https://nodejs.org/api/n-api.html .
I have used C++ because of optimization and speed i can also use Python or Javascript to write the algorithm but the speed of execution will be very low in that and we won't get good optimization. 

<hr>

## Techstack

1) Node.js
2) MongoDB
3) C++
4) NAPI
5) Express

<hr>

## How to run the project?

To run the project you should follow this step:

1) Add this directory to your local system:
```
git remote add origin git@github.com:BeingPratham/Algorithm_PrimeNumber.git
```

2) Now you need to install the packages:
```
npm install
```

3) Now you need to install the build file and for that you need to run this two commands:
```
powershell -ExecutionPolicy Bypass -Command "node-gyp configure"
powershell -ExecutionPolicy Bypass -Command "node-gyp build" 
```

4) Now you can run the server:
```
node server.js
```

5) To test the code then you can use POSTMAN to call the api in post method you can give here ("sieve" / "simple"):
```
POST http://localhost:3000/generatePrimes
body : {
    "start":1,
    "end":100,
    "algorithm":"sieve"
}
```

Sieve is used for optimized algorithm and simple is not optimized.
<hr>

# Thank You

