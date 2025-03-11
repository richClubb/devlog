#!/usr/bin/python3

import pytest

# from context import uint8
from python_int_math import uint8


@pytest.mark.parametrize(
    "a, b, expected_result",
    [
        pytest.param(1, 2, 3, id="Basic 1 + 2 = 3"),
        pytest.param(254, 1, 255, id="Near upper bounds"),
        pytest.param(254, 2, 255, id="Non wrapping test"),
    ]
)
def test_python_uint8_add(a, b, expected_result):

    assert uint8.uint8_add(a, b) == expected_result

@pytest.mark.parametrize(
    "a, b, expected_result",
    [
        pytest.param(3, 1, 2, id="Basic 3 - 1 = 3"),
        pytest.param(2, 2, 0, id="Near lower bounds"),
        pytest.param(2, 3, 0, id="Non wrapping test"),
    ]
)
def test_python_uint8_sub(a, b, expected_result):

    assert uint8.uint8_sub(a, b) == expected_result