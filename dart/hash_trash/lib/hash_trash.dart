import 'dart:math';

import 'package:ansicolor/ansicolor.dart';
import 'package:meta/meta.dart';

String bin({int value, int length}) {
  var result = '';
  for (var i = 1 << 62; i > 0; i = i ~/ 2) {
    print(i);
    result += (value & i) == 1 ? '1' : '0';
  }
  return result;
}

int getHash({@required int value, int hash_bits = 256, int base_simple = 251}) {
  return (pow(base_simple, value).toInt()) % hash_bits;
}

List<int> getRandomX({@required int length, int exponent = 20}) {
  final random = Random();
  var x = <int>[];
  for (var i = 0; i <= length; i++) {
    x.add(random.nextInt(pow(2, exponent).toInt()));
  }
  return x;
}

String highlightDiff({@required String left, @required String right}) {
  var result = '';
  var pen = AnsiPen()..red();
  for (var i = 0; i < min(left.length, right.length); i++) {
    result += (left[i] == right[i]) ? left[i] : pen(left[i]);
  }
  return result;
}
