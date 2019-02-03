const String messageHtml = R"##(<html>
<head>
<title>ESP8266 Message Board</title>
</head>

<body>
  <form action="/">
    Message: <input type="text" name="message">
    Update Delay (ms): <input type="number" name="delayMs" value=0 min=0 max=10000>
    Scroll direction:
    <input type="radio" name="scrollDirection" value="left" checked="checked">Left<br>
    <input type="radio" name="scrollDirection" value="right">Right<br>
    <input type="radio" name="scrollDirection" value="none">None<br>  
    <input type="submit" formmethod="post" value="Submit">
  </form>
</body>

</html>)##";