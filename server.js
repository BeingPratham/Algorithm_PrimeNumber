const express = require('express');
const bodyParser = require('body-parser');
const mongoose = require('mongoose');
const addon = require('./build/Release/addon');

const app = express();
app.use(bodyParser.json());

// Connect to MongoDB
mongoose.connect('MONGODB_URI');
const db = mongoose.connection;
db.on('error', console.error.bind(console, 'MongoDB connection error:'));
db.once('open', () => {
  console.log('Connected to MongoDB');
});

const PrimeResult = require('./models/PrimeResult');

// Route for prime number generation
app.post('/generatePrimes', async (req, res) => {
  const { start, end, algorithm } = req.body;

  // Execute prime number generation
  let primeResult;
  try {
    primeResult = addon.generatePrimeNumbers(parseInt(start), parseInt(end), algorithm);

  } catch (error) {
    return res.status(400).json({ error: 'Invalid input or algorithm' });
  }

  // Create a new PrimeResult record
  const newPrimeResult = new PrimeResult({
    timestamp: new Date(),
    range: { start, end },
    algorithm,
    elapsed_time: primeResult.elapsedTime,
    primes: primeResult.primes.length,
  });

  // Save to MongoDB
  try {
    await newPrimeResult.save();
    res.json(primeResult);
  } catch (error) {
    res.status(500).json({ error: 'Failed to save prime result' });
  }
});

const PORT = 3000;
app.listen(PORT, () => {
  console.log(`Server is running on http://localhost:${PORT}`);
});
