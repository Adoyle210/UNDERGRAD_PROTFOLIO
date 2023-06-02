var mysql = require('mysql')
var creds = require('./credentials.json')

var pool = mysql.createPool({
  connectionLimit : 10,
  host : 'classmysql.engr.oregonstate.edu',
  user : creds.username,
  password : creds.password,
  database : creds.database
})

module.exports.pool = pool