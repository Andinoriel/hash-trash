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

double correlationCoefficient({List<int> x, List<int> y}) {
  var length = min(x.length, y.length);
  var avgX = 0.0;
  var avgY = 0.0;
  var avgX2 = 0.0;
  var avgY2 = 0.0;
  for (var i = 0; i < length; i++) {
    avgX += x[i];
    avgY += y[i];
    avgX2 += x[i] * x[i];
    avgY2 += y[i] * y[i];
  }
  avgX /= length;
  avgY /= length;
  avgX2 /= length;
  avgY2 /= length;
  var deltaX2 = avgX2 - avgX * avgX;
  var deltaY2 = avgY2 - avgY * avgY;
  var deltaX = sqrt(deltaX2);
  var deltaY = sqrt(deltaY2);
  var numerator = 0.0;
  for (var i = 0; i < length; i++) {
    numerator += (x[i] - avgX) * (y[i] - avgY);
  }
  var denominator = length * deltaX * deltaY;
  var corrCoef = numerator / denominator;
  return corrCoef;
}
