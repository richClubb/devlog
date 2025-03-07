import pytest

from python_int_math import python_uint8_add


@pytest.mark.parametrize(
    "a, b, expected_result",
    [
        pytest.param(1, 2, 3, id="Basic 1+2 = 3"),
        pytest.param(254, 1, 255, id="Near upper bounds"),
        pytest.param(254, 2, 255, id="Non wrapping test"),
    ]
)
def test_python_uint8_add(a, b, expected_result):

    assert python_uint8_add(a, b) == expected_result