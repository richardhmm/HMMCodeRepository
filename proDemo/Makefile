
include $(TOPDIR)/rules.mk

PKG_NAME:=proDemo
PKG_VERSION:=1.0.0
PKG_RELEASE=1


PKG_LICENSE:=richardhmm
# Note: Packaging is maintained upstream at
PKG_MAINTAINER:=richardhmm <sunhyx@gmail.com>
PKG_LICENSE_FILES:=COPYING


PKG_FIXUP:=autoreconf
# do not run make install
PKG_INSTALL:=0
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(BUILD_VARIANT)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/proDemo/Default
  SUBMENU:=openwrt project demo
  SECTION:=net
  CATEGORY:=Network
  DEPENDS:=+libpthread
  TITLE:=openwrt project demo
endef

define Package/proDemo
$(call Package/proDemo/Default)
  VARIANT:=normal
endef


define Package/proDemo/description
	The proDemo project is a demo.
endef


define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) -rf ./proDemo/* $(PKG_BUILD_DIR)
endef

define Package/proDemo/configure
	$(call Build/Configure/Default)
endef

define Package/proDemo/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/proDemo $(1)/usr/bin/
#	$(CP) $(PKG_BUILD_DIR)/scripts/test.sh $(1)/usr/bin
endef

$(eval $(call BuildPackage,proDemo))
