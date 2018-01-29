// Copyright 2015 Google Inc. All rights reserved.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd

#ifndef MPD_BASE_MOCK_MPD_BUILDER_H_
#define MPD_BASE_MOCK_MPD_BUILDER_H_

#include <gmock/gmock.h>

#include "packager/base/compiler_specific.h"
#include "packager/base/synchronization/lock.h"
#include "packager/mpd/base/adaptation_set.h"
#include "packager/mpd/base/content_protection_element.h"
#include "packager/mpd/base/mpd_builder.h"
#include "packager/mpd/base/period.h"
#include "packager/mpd/base/representation.h"

namespace shaka {

class MockMpdBuilder : public MpdBuilder {
 public:
  MockMpdBuilder();
  ~MockMpdBuilder() override;

  MOCK_METHOD1(GetOrCreatePeriod, Period*(double start_time_in_seconds));
  MOCK_METHOD1(ToString, bool(std::string* output));
};

class MockPeriod : public Period {
 public:
  MockPeriod(uint32_t period_id, double start_time_in_seconds);

  MOCK_METHOD2(GetOrCreateAdaptationSet,
               AdaptationSet*(const MediaInfo& media_info,
                              bool content_protection_in_adaptation_set));

 private:
  // Only for constructing the super class. Not used for testing.
  base::AtomicSequenceNumber sequence_counter_;
};

class MockAdaptationSet : public AdaptationSet {
 public:
  // |adaptation_set_id| is the id for the AdaptationSet.
  explicit MockAdaptationSet(uint32_t adaptation_set_id);
  ~MockAdaptationSet() override;

  MOCK_METHOD1(AddRepresentation, Representation*(const MediaInfo& media_info));
  MOCK_METHOD1(CopyRepresentation,
               Representation*(const Representation& representation));
  MOCK_METHOD1(AddContentProtectionElement,
               void(const ContentProtectionElement& element));
  MOCK_METHOD2(UpdateContentProtectionPssh,
               void(const std::string& drm_uuid, const std::string& pssh));
  MOCK_METHOD1(AddRole, void(AdaptationSet::Role role));
  MOCK_METHOD1(ForceSetSegmentAlignment, void(bool segment_alignment));
  MOCK_METHOD1(AddAdaptationSetSwitching, void(uint32_t adaptation_set_id));
  MOCK_METHOD1(AddTrickPlayReferenceId, void(uint32_t id));

 private:
  // Only for constructing the super class. Not used for testing.
  base::AtomicSequenceNumber sequence_counter_;
};

class MockRepresentation : public Representation {
 public:
  // |representation_id| is the numeric ID for the <Representation>.
  explicit MockRepresentation(uint32_t representation_id);
  ~MockRepresentation() override;

  MOCK_METHOD1(AddContentProtectionElement,
               void(const ContentProtectionElement& element));
  MOCK_METHOD2(UpdateContentProtectionPssh,
               void(const std::string& drm_uuid, const std::string& pssh));
  MOCK_METHOD3(AddNewSegment,
               void(uint64_t start_time, uint64_t duration, uint64_t size));
  MOCK_METHOD1(SetSampleDuration, void(uint32_t sample_duration));
  MOCK_CONST_METHOD0(GetMediaInfo, const MediaInfo&());
};

}  // namespace shaka

#endif  // MPD_BASE_MOCK_MPD_BUILDER_H_
