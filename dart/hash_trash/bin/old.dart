import 'dart:math';

int getHash(int x, int n, {int a = 251}) {
  return (pow(a, x).toInt()) % n;
}

List<int> getRandomX(len) {
  final random = new Random();
  List<int> x = [];
  for (var i = 0; i <= len; i++) {
    x.add(random.nextInt(pow(2, 20).toInt()));
  }
  return x;
}

main(List<String> args) {
  var n = pow(2, 8).toInt();
  var x = getRandomX(10);
  List<int> y = [];
  print("x: $x");
  for (var element in x) {
    y.add(getHash(element, n));
  }
  print("y: $y");
  for (int i = 0; i < y.length; i++) {
    x[i] ^= 1 << i;
  }
  print("x_: $x");
  y.clear();
  for (var element in x) {
    y.add(getHash(element, n));
  }
  print("y_: $y");
}
