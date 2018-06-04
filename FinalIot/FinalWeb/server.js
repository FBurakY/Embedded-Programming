const express = require('express')
const app = express()
const port = 80

app.get('', (request, response) => {
  response.send('Hello from Express!')
  console.log("sended");
})




function send_data (data = "")
https.get("http://192.168.43.178:80/?pin=on/ ", (resp) => {
  let data = '';
  // A chunk of data has been recieved.
  resp.on('data', (chunk) => {
    data += chunk;
  });






app.listen(port, (err) => {
  if (err) {
    return console.log('something bad happened', err)
  }











































  console.log(`server is listening on ${port}`)
})



