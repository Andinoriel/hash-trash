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

List<int> countCollisionBetween(List<int> x, List<int> y) {
  var collisions = <int>[];
  for (var i = 0; i < min(x.length, y.length); i++) {
    if (x[i] == y[i]) {
      collisions.add(x[i]);
    }
  }
  return collisions;
}

Map<int, int> countCollisions(List<int> x) {
  var collisions = <int, int>{};
  for (var i = 0; i < x.length - 1; i++) {
    if (collisions.containsKey(x[i])) {
      collisions[x[i]]++;
    } else {
      collisions[x[i]] = 1;
    }
  }
  var new_collisions = <int, int>{};
  for (var key in collisions.keys) {
    if (collisions[key] > 1) {
      new_collisions[key] = collisions[key];
    }
  }
  return new_collisions;
}

int getHash({@required int value, int hash_bits = 256, int base_simple = 251}) {
  return (pow(base_simple, value).toInt()) % hash_bits;
}

String getOutputLine(
    {@required int left,
    @required String binLeft,
    @required String binRight,
    @required Map<int, int> collisions,
    @required int hashLeft,
    @required int hashRight}) {
  var pen = AnsiPen()..red();
  var result = '${left.toString().padLeft(20, ' ')}\t\t';
  result += '${highlightDiff(left: binLeft, right: binRight)}\t\t';
  result += 'H(x)' +
      (collisions.keys.contains(hashLeft)
          ? pen(hashLeft.toString().padLeft(20, ' '))
          : hashLeft.toString().padLeft(20, ' ')) +
      '\t\t';
  result += 'H(X) = H(Y) = ${hashLeft == hashRight}';
  return result;
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
