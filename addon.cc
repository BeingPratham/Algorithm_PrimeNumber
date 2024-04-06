#include <napi.h>
#include <node_api.h>
#include <vector>
#include <chrono>  // For timing

namespace addon {

  using namespace Napi; // We define this so we don't have to use this everytime

  bool isPrime(int num) { // This is just a function to check if number is prime or not with brute force method
    if (num <= 1) {
      return false;
    }
    for (int i = 2; i * i <= num; ++i) {
      if (num % i == 0) {
        return false;
      }
    }
    return true;
  }

  Object Algorithms(const CallbackInfo& info) {
    Env env = info.Env(); //This env object is used for operations that require interaction with the JavaScript environment, such as creating, manipulating, or returning JavaScript values.

    if (info.Length() < 3 || !info[0].IsNumber() || !info[1].IsNumber() || !info[2].IsString()) {
      TypeError::New(env, "Expected three arguments: start (number), end (number), algorithm (string)").ThrowAsJavaScriptException();
      return Object::New(env); // Return empty object in case of error
    }

    int start = info[0].As<Number>().Int32Value(); // The first value which we got from backend : [0]
    int end = info[1].As<Number>().Int32Value(); // The second value : [1]
    std::string algorithm = info[2].As<String>().Utf8Value(); // The third value : [2]

    if (start < 0 || end < 0) {
      TypeError::New(env, "Numbers must be non-negative").ThrowAsJavaScriptException();
      return Object::New(env); // Return empty object in case of error
    }

    auto start_time = std::chrono::steady_clock::now();  // Start timing

    Array result = Array::New(env);
    int index = 0;

    if (algorithm == "sieve") {
      // Use Sieve of Eratosthenes algorithm : This is an optimized algorithm
      std::vector<bool> primes(end + 1, true); // To add all the primes in the vector
      primes[0] = primes[1] = false; // 0 and 1 are not prime so we are just assigning them as false

      for (int p = 2; p * p <= end; p++) { 
        if (primes[p] == true) { // If any number is not checked then we check for that
          for (int i = p * p; i <= end; i += p) { 
            primes[i] = false; // This loop checks for all the multiples and assigning them false
          }
        }
      }

      for (int i = start; i <= end; i++) {
        if (primes[i]) { // If any number from start to left is left true then they are primes and we can add them in result
          result.Set(index++, i);
        }
      }
    } else if (algorithm == "simple") {
      // Use Simple Algorithm : This will take long time and not well optimized
      for (int num = start; num <= end; ++num) { // This directly loops from start to end and call the function everytime
        if (isPrime(num)) {
          result.Set(index++, num);
        }
      }
    } else {
      TypeError::New(env, "Unknown algorithm. Choose 'sieve' or 'simple'").ThrowAsJavaScriptException();
      return Object::New(env); // Return empty object in case of error
    }

    auto end_time = std::chrono::steady_clock::now();  // End timing
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();  // Calculate elapsed time

    Function consoleLog = env.Global().Get("console").As<Object>().Get("log").As<Function>();
    consoleLog({String::New(env, "Execution time for " + algorithm + " algorithm: " + std::to_string(elapsed_time) + " ms")});

    // Create the return object with prime numbers and elapsed time
    Object returnObject = Object::New(env);
    returnObject.Set("primes", result); //It will return prime number lists
    returnObject.Set("elapsedTime", elapsed_time); // Then it will return elapsed time with it

    return returnObject;
  }

} // namespace addon

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  // We are exporting our algorithm with this so in node.js if we have to use Algorithms function then we can use with generatePrimeNumbers
  exports.Set(Napi::String::New(env, "generatePrimeNumbers"),
              Napi::Function::New(env, addon::Algorithms));
  return exports;
}


// It is used to define the entry point for the native addon
// addon : It is the name of the module
// Init : It is for initialization and it will tell Node.js which function to call when the module is loaded
NODE_API_MODULE(addon, Init)
