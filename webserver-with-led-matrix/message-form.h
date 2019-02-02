const String messageHtml = R"##(<html>
<head>
<title>ESP8266 Message Board</title>
</head>

<body>
  <form action="/">
    Message: <input type="text" name="message">
    Update Delay (ms): <input type="number" name="delayMs" value=0 min=0 max=10000>
    <input type="submit" formmethod="post" value="Submit">
  </form>
</body>

</html>)##";