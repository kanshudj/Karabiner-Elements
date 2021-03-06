#include <catch2/catch.hpp>

#include "types.hpp"

TEST_CASE("device_identifiers") {
  {
    krbn::device_identifiers di(krbn::vendor_id(1234),
                                krbn::product_id(5678),
                                true,
                                false);
    REQUIRE(di.is_apple() == false);
  }
  {
    krbn::device_identifiers di(krbn::vendor_id(1452),
                                krbn::product_id(610),
                                true,
                                false);
    REQUIRE(di.is_apple() == true);
  }
  {
    auto di = krbn::device_identifiers::make_from_json(nlohmann::json::object());
    REQUIRE(di.get_vendor_id() == krbn::vendor_id(0));
    REQUIRE(di.get_product_id() == krbn::product_id(0));
    REQUIRE(di.get_is_keyboard() == false);
    REQUIRE(di.get_is_pointing_device() == false);
  }
  {
    auto json = nlohmann::json::object({
        {"vendor_id", 1234},
        {"product_id", 5678},
        {"is_keyboard", true},
        {"is_pointing_device", false},
        {"dummy key", "dummy value"},
    });

    auto di = krbn::device_identifiers::make_from_json(json);
    REQUIRE(di.get_vendor_id() == krbn::vendor_id(1234));
    REQUIRE(di.get_product_id() == krbn::product_id(5678));
    REQUIRE(di.get_is_keyboard() == true);
    REQUIRE(di.get_is_pointing_device() == false);
    REQUIRE(di.to_json() == json);
  }
  {
    auto json = nlohmann::json::object({
        {"is_pointing_device", true},
    });

    auto di = krbn::device_identifiers::make_from_json(json);
    REQUIRE(di.get_is_pointing_device() == true);
  }
}
