// Initialize a class field in a record with an initializer
record Container {
  var y;

  proc init() {
    y = new Stored(true);

    super.init();
  }

  proc deinit() {
    delete y;
  }
}

class Stored {
  var x: bool;

  proc init(xVal) {
    x = xVal;

    super.init();
  }
}

var c = new Container();

writeln(c);
