const mongoose = require('mongoose');

// This is just a schema for the mongodb so we can define on how to store the data.
const primeResultSchema = new mongoose.Schema({
  range: {
    start: { type: Number, required: true },
    end: { type: Number, required: true },
  },
  algorithm: { type: String, required: true },
  elapsed_time: { type: Number, required: true },
  primes: { type: Number, required: true },
}, { timestamps: true }); // Include timestamps option

const PrimeResult = mongoose.model('PrimeResult', primeResultSchema);

module.exports = PrimeResult;
